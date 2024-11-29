import smbus2
import time
from inputs import get_gamepad
import math
import threading
import Jetson.GPIO as GPIO
from canvas import Canvas


# Set up GPIO 
SENSOR_PIN = 17  # GPIO pin connected to the LM393 output 
pulsos = 0
ultimo_tempo = time.time()
RODA_DIAMETRO = 0.065  # Diâmetro da roda em metros
FUROS = 36


 
def pulso_detectado(channel):
   global pulsos
   pulsos += 1
def calcular_velocidade(pulsos, tempo):
   voltas = pulsos / FUROS
   distancia = voltas * (RODA_DIAMETRO * 3.14159)  # Distância em metros
   velocidade_ms = distancia / tempo
   velocidade_kmh = velocidade_ms * 3.6
   return velocidade_kmh

#GPIO.add_event_detect(SENSOR_PIN, GPIO.RISING, callback=pulso_detectado) 


class JetCar:
    def __init__(self, servo_addr=0x40, motor_addr=0x60):
        # Servo setup

        self.canvas = Canvas()

        self.servo_bus = smbus2.SMBus(1)
        self.SERVO_ADDR = servo_addr
        self.STEERING_CHANNEL = 0
        
        # Servo config
        self.MAX_ANGLE = 180
        self.SERVO_CENTER_PWM = 307
        self.SERVO_LEFT_PWM = 225
        self.SERVO_RIGHT_PWM = 389
        
        # Motor controller setup
        self.motor_bus = smbus2.SMBus(1)
        self.MOTOR_ADDR = motor_addr
        
        # Control flags
        self.running = False
        self.current_speed = 0
        self.current_angle = 0
        #find /usr/include -name i2c-dev.h
        # Initialize both systems
        self.init_servo()
        self.init_motors()
        
    def init_servo(self):
        try:
            # Reset PCA9685
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0x00, 0x06)
            time.sleep(0.1)
            
            # Setup servo control
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0x00, 0x10)
            time.sleep(0.1)
            
            # Set frequency (~50Hz)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0xFE, 0x79)
            time.sleep(0.1)
            
            # Configure MODE2
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0x01, 0x04)
            time.sleep(0.1)
            
            # Enable auto-increment
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0x00, 0x20)
            time.sleep(0.1)
            
            return True
        except Exception as e:
            print(f"Servo init error: {e}")
            return False

    def init_motors(self):
        try:
            # Configure motor controller
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x00, 0x20)
            
            # Set frequency to 60Hz
            prescale = int(math.floor(25000000.0 / 4096.0 / 60 - 1))
            oldmode = self.motor_bus.read_byte_data(self.MOTOR_ADDR, 0x00)
            newmode = (oldmode & 0x7F) | 0x10
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x00, newmode)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0xFE, prescale)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x00, oldmode)
            time.sleep(0.005)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x00, oldmode | 0xa1)
            
            return True
        except Exception as e:
            print(f"Motor init error: {e}")
            return False


    def set_steering(self, angle):
        """Set steering angle (-90 to +90 degrees)"""
        angle = max(-self.MAX_ANGLE, min(self.MAX_ANGLE, angle))
        
        if angle < 0:
            pwm = int(self.SERVO_CENTER_PWM + 
                     (angle / self.MAX_ANGLE) * (self.SERVO_CENTER_PWM - self.SERVO_LEFT_PWM))
        elif angle > 0:
            pwm = int(self.SERVO_CENTER_PWM + 
                     (angle / self.MAX_ANGLE) * (self.SERVO_RIGHT_PWM - self.SERVO_CENTER_PWM))
        else:
            pwm = self.SERVO_CENTER_PWM
            
        self.set_servo_pwm(self.STEERING_CHANNEL, 0, pwm)
        self.current_angle = angle

    def set_angle(self, angle):
        self.set_servo_pwm(self.STEERING_CHANNEL, 0, angle)

    def angle_to_pwm(self, angle):
        """
        Converte ângulo (-90 a +90) para valor PWM
        Ângulo negativo = esquerda
        Ângulo positivo = direita
        Ângulo zero = centro
        """
        # Limita o ângulo entre -90 e +90
        angle = max(-self.MAX_ANGLE, min(self.MAX_ANGLE, angle))
        
        if angle < 0:  # Esquerda
            # Interpola entre centro e esquerda
            return int(self.SERVO_CENTER_PWM + 
                      (angle / self.MAX_ANGLE) * (self.SERVO_CENTER_PWM - self.SERVO_LEFT_PWM))
        elif angle > 0:  # Direita
            # Interpola entre centro e direita
            return int(self.SERVO_CENTER_PWM + 
                      (angle / self.MAX_ANGLE) * (self.SERVO_RIGHT_PWM - self.SERVO_CENTER_PWM))
        else:  # Centro
            return self.SERVO_CENTER_PWM

   # def set_angle(self, angle):
   #     """
   #     Define o ângulo do servo (-180 a +180 graus)
   #     Negativo = Esquerda
   #     Positivo = Direita
   #     Zero = Centro
   #     """
   #     if not isinstance(angle, (int, float)):
   #         print("Ângulo deve ser um número")
   #         return False
   #         
   #     if abs(angle) > self.MAX_ANGLE:
   #         print(f"Ângulo deve estar entre -{self.MAX_ANGLE} e +{self.MAX_ANGLE} graus")
   #         return False
   #     
   #     direction = "centro" if angle == 0 else "esquerda" if angle < 0 else "direita"
   #     print(f"Movendo servo para {abs(angle)}° ({direction})")
   #     
   #     pwm_value = self.angle_to_pwm(angle)
   #     return self.set_pwm(self.STEERING_CHANNEL, 0, pwm_value)
#
    def set_servo_pwm(self, channel, on_value, off_value):
        """Set PWM values for servo"""
        try:
            base_reg = 0x06 + (channel * 4)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, base_reg, on_value & 0xFF)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, base_reg + 1, on_value >> 8)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, base_reg + 2, off_value & 0xFF)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, base_reg + 3, off_value >> 8)
            return True
        except Exception as e:
            print(f"Servo PWM error: {e}")
            return False

    def set_motor_pwm(self, channel, value):
        """Set PWM value for motor channel"""
        value = min(max(value, 0), 4095)
        try:
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x06 + 4 * channel, 0)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x07 + 4 * channel, 0)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x08 + 4 * channel, value & 0xFF)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x09 + 4 * channel, value >> 8)
        except Exception as e:
            print(f"Motor PWM error: {e}")

    def set_speed(self, speed):
        """Set motor speed (-100 to +100)"""
        speed = max(-100, min(100, speed))
        pwm_value = int(abs(speed) / 100.0 * 4095)
        
        if speed > 0:  # Forward
            self.set_motor_pwm(0, pwm_value)  # IN1
            self.set_motor_pwm(1, 0)          # IN2
            self.set_motor_pwm(2, pwm_value)  # ENA

            self.set_motor_pwm(5, pwm_value)  # IN3
            self.set_motor_pwm(6, 0)          # IN4
            self.set_motor_pwm(7, pwm_value)  # ENB
        elif speed < 0:  # Backward
            self.set_motor_pwm(0, pwm_value)  # IN1
            self.set_motor_pwm(1, pwm_value)  # IN2
            self.set_motor_pwm(2, 0)          # ENA

            self.set_motor_pwm(6, pwm_value)  # IN3
            self.set_motor_pwm(7, pwm_value)  # IN4
            self.set_motor_pwm(8, 0)          # ENB
        else:  # Stop
            for channel in range(9):
                self.set_motor_pwm(channel, 0)
        
        self.current_speed = speed
    def process(self):
        global ultimo_tempo
        global pulsos 
        if time.time() - ultimo_tempo >= 1:
            kmh = calcular_velocidade(pulsos, 1)
            print(f"Velocidade {kmh:.2f} km/h")
            pulsos = 0
            ultimo_tempo = time.time()
            self.canvas.clear()
            self.canvas.draw_text(1,2,f" {kmh:.2f} km/h",1)
            
        return self.running

    def process_joystick(self):
        print("Gamepad control started")
        print("Left stick: steering")
        print("RT: forward, LT: reverse")
        print("START/SELECT: exit")
        while self.running:
            try:
                events = get_gamepad()
                self.process()
                for event in events:
                    #print(event.code)
                    if event.code == 'ABS_X':
                        speed = int((-event.state / 32767) * 100)
                        current_angle = ((event.state - 127) / 127) * 100

                      

                        print(speed," ,",current_angle,",",event.state)
                        
                        self.set_steering(current_angle)
                        
                    
                        
                    elif event.code == 'ABS_GAS':
                        self.current_speed = event.state / 255.0 * 100
                        self.set_speed(self.current_speed)
                    elif event.code == 'ABS_BRAKE':
                        self.current_speed = -event.state / 255.0 * 100
                        self.set_speed(self.current_speed)
                    elif event.code in ['BTN_START', 'BTN_SELECT'] and event.state == 1:
                        self.running = False
                        break
                
            except KeyboardInterrupt:
                self.running = False
                break
            except Exception as e:
                print(f"Gamepad error: {e}")
                continue

    def start(self):
        """Start the car control"""
        self.running = True
        self.joystick_thread = threading.Thread(target=self.process_joystick)
        self.joystick_thread.start()

    def stop(self):
        """Stop the car and cleanup"""
        self.running = False
        if hasattr(self, 'joystick_thread'):
            self.joystick_thread.join()
        self.set_speed(0)
        self.set_steering(0)
        self.servo_bus.close()
        self.motor_bus.close()
        GPIO.cleanup()


# car = None

# car = JetCar()
# #car.set_speed(-100)
# #car.set_steering(-180)
# car.set_angle(30)
# time.sleep(2)
# car.set_speed(0)
# car.set_steering(0)
# car.servo_bus.close()
# car.motor_bus.close()

# pulsos = 0
# ultimo_tempo = time.time()


# pulsos = 0
# ultimo_tempo = time.time()


# RODA_DIAMETRO = 0.065  # Diâmetro da roda em metros
# FUROS = 36

# pulsos = 0
# ultimo_tempo = time.time()

# def pulso_detectado(channel):
#    global pulsos
#    pulsos += 1

# def calcular_velocidade(pulsos, tempo):
#    voltas = pulsos / FUROS
#    distancia = voltas * (RODA_DIAMETRO * 3.14159)  # Distância em metros
#    velocidade_ms = distancia / tempo
#    velocidade_kmh = velocidade_ms * 3.6
#    return velocidade_kmh


try:
    car = JetCar()
    canvas = Canvas()
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(17, GPIO.IN)  # DO pin


    GPIO.add_event_detect(17, GPIO.RISING, callback=pulso_detectado)

    car.set_speed(100)
    velocidade_maxima=1
    kmh =0
    while True:
        canvas.clear()
        if time.time() - ultimo_tempo >= 1:
           kmh = calcular_velocidade(pulsos, 1)
           if kmh > velocidade_maxima:
               velocidade_maxima = kmh
           print(f"Velocidade {kmh:.2f} km/h")
           pulsos = 0
           ultimo_tempo = time.time()

        canvas.draw_text(1,1,f" {kmh:.2f} km/h",1)
        canvas.draw_text(1,10,f" {velocidade_maxima:.2f} km/h Maximo",1)
        
        filled = int((kmh / velocidade_maxima) * 100)
        canvas.draw_rect(2,25,filled,8,True)
        canvas.update()
        time.sleep(0.1)

    #car.start()
    #3while car.running:
    #    time.sleep(0.1)
except Exception as e:
    print(f"Error: {e}")
finally:
    car.stop()
    canvas.clear()
    canvas.update()
    GPIO.cleanup()
    print("Program ended") 



# car = None

# try:
#     car = JetCar()
#     car.start()

#     while car.running:
#          time.sleep(0.001)

# except Exception as e:
#     print(f"Error: {e}")
# finally:
#     car.stop()


print("Program ended") 