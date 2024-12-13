#include "FServo.hpp"

FServo::FServo(){
	i2c_device = "/dev/i2c-1";
	_fdServo = open(i2c_device.c_str(), O_RDWR);
	if (_fdServo < 0)
		throw std::runtime_error("Error open I2C");
	if ( ioctl(_fdServo, I2C_SLAVE, _servoAddr) < 0){
		close (_fdServo);
		throw std::runtime_error("Erro ao configurar endereço I2C do servo.");
	}
}

FServo::~FServo(){
	close(_fdServo);
    std::cout << "destructor call\n";
}

bool FServo::init_servo(){
	try{
		    // Reset PCA9685
			writeByteData(_fdServo, 0x00, 0x06);
			usleep(100000); // Aguarda 100 ms
			
			// Setup servo control
			writeByteData(_fdServo, 0x00, 0x10);
			usleep(100000);

			// Set frequency (~50Hz)
			writeByteData(_fdServo, 0xFE, 0x79);
			usleep(100000);

			// Configure MODE2
			writeByteData(_fdServo, 0x01, 0x04);
			usleep(100000);

			// Enable auto-increment
			writeByteData(_fdServo, 0x00, 0x20);
			usleep(100000);
		return true;
	}
	catch(const std::exception &e){
		std::cerr << "Erro ao inicializar o servo: " << e.what() << std::endl;
		return false;
	}
}

bool FServo::setServoPwm(const int channel, int on_value, int off_value){
	try{
		writeByteData(_fdServo, 0x06 + 4 * channel, on_value & 0xFF);
		writeByteData(_fdServo, 0x07 + 4 * channel, on_value >> 8);
		writeByteData(_fdServo, 0x08 + 4 * channel, off_value & 0xFF);
		writeByteData(_fdServo, 0x09 + 4 * channel, off_value >> 8);
		return true;
	}
	catch(const std::exception &e){
		std::cerr << "Erro ao configurar PWM do servo: " << e.what() << std::endl;
		return false;
	}
}

void FServo::set_steering(int angle){
    /* """Set steering angle (-90 to +90 degrees)""" */
	angle = std::max(-_maxAngle, std::min(_maxAngle, angle));
	
	int pwm;
	if (angle < 0){
		// Calcula o PWM para ângulo negativo
		pwm = static_cast<int>(_servoCenterPwm + (static_cast<float>(angle) / _maxAngle) * (_servoCenterPwm - _servoLeftPwm));
	}
	else if (angle > 0){
		 // Calcula o PWM para ângulo positivo
		 pwm = static_cast<int>(_servoCenterPwm + (static_cast<float>(angle) / _maxAngle) * (_servoRightPwm - _servoCenterPwm));
	}
	else 
		pwm = _servoCenterPwm;
	setServoPwm(_sterringChannel, 0 , pwm);
	_currentAngle = angle;
}

void FServo::writeByteData(int fd, uint8_t reg, uint8_t value) {
	uint8_t buffer[2] = {reg, value};
	if (write(fd, buffer, 2) != 2) {
		throw std::runtime_error("Erro ao escrever no dispositivo I2C.");
	}
}

uint8_t FServo::readByteData(int fd, uint8_t reg){
	if(write(fd, &reg, 1) != 1)
		throw std::runtime_error("Erro ao enviar o registrador ao dispositivo I2C.");
	uint8_t value;
	if (read(fd, &value, 1) != 1)
		throw std::runtime_error("Erro ao ler o registrador ao dispositivo I2C.");
	return value;
}

// Função de tratamento de sinal para interromper o programa com Ctrl+C
void signalHandler(int signum) {
	(void)signum;
    std::cout << "\nInterrupção recebida, parando os motores..." << std::endl;
    //running = false;
}

int main() {
    // Conectar o manipulador de sinal ao SIGINT
    signal(SIGINT, signalHandler);

    try {
        FServo motors;

        // Inicializar servo e motores
        if (!motors.init_servo()) {
            std::cerr << "Falha na inicialização do servo.\n";
            return 1;
        }

        std::cout << "Inicialização completa. Testando funções...\n";

        // Testar controle de direção
        std::cout << "Definindo ângulo de direção para -45 graus...\n";
        motors.set_steering(-45);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "Definindo ângulo de direção para +45 graus...\n";
        motors.set_steering(45);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "Centralizando direção...\n";
        motors.set_steering(0);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "Teste concluído com sucesso.\n";
    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
