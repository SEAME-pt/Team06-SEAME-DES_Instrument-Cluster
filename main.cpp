#include "Motors.hpp"

int main() {
    struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        std::cerr << "Erro ao abrir o chip GPIO!" << std::endl;
        return 1;
    }

    struct gpiod_line *line = gpiod_chip_get_line(chip, 17); // Número do pino do sensor
    if (!line) {
        std::cerr << "Erro ao obter a linha GPIO!" << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    // Configura a linha para detectar bordas de subida e descida
    if (gpiod_line_request_both_edges_events(line, "teste") < 0) {
        std::cerr << "Erro ao configurar a linha para eventos!" << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    struct gpiod_line_event event;
    while (true) {
        int ret = gpiod_line_event_wait(line, nullptr); // Espera indefinidamente por um evento
        if (ret > 0) {
            gpiod_line_event_read(line, &event);
            std::cout << "Evento detectado: " << event.event_type << std::endl;
        } else if (ret < 0) {
            std::cerr << "Erro ao esperar por eventos GPIO!" << std::endl;
            break;
        }
    }

    gpiod_chip_close(chip);
    return 0;
}

/* int main() {
    // Configura o manipulador de sinal para capturar Ctrl+C (SIGINT)
    std::signal(SIGINT, signalHandler);

    try {
        // Inicializa a classe Motors
        Motors jetCar;

        // Inicializa o servo e os motores
        if (!jetCar.init_servo()) {
            std::cerr << "Erro ao inicializar o servo." << std::endl;
            return 1;
        }
        if (!jetCar.init_motors()) {
            std::cerr << "Erro ao inicializar os motores." << std::endl;
            return 1;
        }

        std::cout << "Sistema inicializado com sucesso!" << std::endl;

        // Configura GPIO para a leitura do sensor de velocidade
        struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip0");
        if (!chip) {
            std::cerr << "Erro ao abrir o chip GPIO!" << std::endl;
            return 1;
        }

        struct gpiod_line *line = gpiod_chip_get_line(chip, 17); // Substitua pelo número do pino correto
        if (!line) {
            std::cerr << "Erro ao obter a linha GPIO!" << std::endl;
            gpiod_chip_close(chip);
            return 1;
        }

        // Configura a linha para detectar bordas de subida e queda
        if (gpiod_line_request_both_edges_events(line, "sensor_velocidade") < 0) {
            std::cerr << "Erro ao configurar GPIO para eventos!" << std::endl;
            gpiod_chip_close(chip);
            return 1;
        }

        // Cria threads para monitorar a velocidade e controlar o movimento
        std::thread monitoramentoThread(&Motors::monitorGPIO, &jetCar, line);
        std::thread velocidadeThread(&Motors::updateVol, &jetCar);

        // Define a velocidade dos motores para iniciar o movimento
        jetCar.setSpeed(-10); // Ajuste a velocidade conforme necessário

        // Enquanto o programa estiver rodando, mantém o loop ativo
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simples pausa para reduzir uso da CPU
        }

        // Para encerrar, interrompe as threads e fecha recursos
        std::cout << "Parando os motores..." << std::endl;
        running.store(false); // Alteração atômica para sinalizar que as threads devem parar
        monitoramentoThread.join();
        velocidadeThread.join();
        jetCar.setSpeed(0); // Para de os motores


        gpiod_line_release(line);
        gpiod_chip_close(chip);

        return 1;
    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
 */



        // Teste de controle do servo (direção)
        //std::cout << "Girando o volante para a esquerda (-45 graus)..." << std::endl;
        //jetCar.set_steering(-45);
        //usleep(1000000); // Aguarda 1 segundo
//
        //std::cout << "Girando o volante para o centro (0 graus)..." << std::endl;
        //jetCar.set_steering(0);
        //usleep(1000000);
//
        //std::cout << "Girando o volante para a direita (+45 graus)..." << std::endl;
        //jetCar.set_steering(45);
        //usleep(1000000);
//
		//std::cout << "Girando o volante para o centro (0 graus)..." << std::endl;
        //jetCar.set_steering(0);
        //usleep(1000000);

        // Teste de controle dos motores (velocidade)
      //  std::cout << "Acelerando para frente (50%)..." << std::endl;
      //  jetCar.setSpeed(100);
      //  usleep(2000000); // Aguarda 2 segundos
//
      //  std::cout << "Reduzindo para 0 (parando)..." << std::endl;
      //  jetCar.setSpeed(0);
      //  usleep(1000000);
//
      //  std::cout << "Recuo (marcha ré, 30%)..." << std::endl;
      //  jetCar.setSpeed(-100);
      //  usleep(2000000);
//
      //  std::cout << "Parando o veículo..." << std::endl;
      //  jetCar.setSpeed(0);
//
      //  std::cout << "Teste concluído com sucesso!" << std::endl;