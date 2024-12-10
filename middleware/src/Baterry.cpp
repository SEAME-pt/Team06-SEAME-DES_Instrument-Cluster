#include "../inc/Baterry.hpp"

Battery::Battery() {
	// Use pre-initialized i2c_bus and adc_address
	std::string i2c_device = "/dev/i2c-" + std::to_string(i2c_bus);
	i2c_fd = open(i2c_device.c_str(), O_RDWR);
	if (i2c_fd < 0)
		throw std::runtime_error("Failed to open I2C bus");
	if (ioctl(i2c_fd, I2C_SLAVE, adc_address) < 0){
		close(i2c_fd);
		throw std::runtime_error("Failed to acquire bus access and/or talk to slave");
	}
}

Battery::~Battery() {
	if (i2c_fd >= 0)
		close(i2c_fd);
}


int Battery::readI2CBlockData(uint8_t reg, uint8_t *data, size_t length) {
	if (write(i2c_fd, &reg, 1) != 1){
		throw std::runtime_error("Failed to write to I2C bus");
		return -1;
	}
	if (read(i2c_fd, data, length) != static_cast<ssize_t>(length)){
		throw std::runtime_error("Failed to read from I2C bus");
		return -1;
	}
	return 0;
}

int Battery::read_adc() {
	uint8_t data[2];
	if (readI2CBlockData(0, data, 2) != 0){
		throw std::runtime_error("Erro na leitura do ADC.");
		return -1;
	}
	return (data[0] << 8) | data[1];
}

float Battery::getVoltage() {
    int adc_value = read_adc();
    float v_measured = (adc_value * ADC_REF) / ADC_MAX;
    float v_battery = v_measured * VOLTAGE_DIVIDER;
    return v_battery;
}

float Battery::getPercentage() {
	float voltage = getVoltage();
	float percentage = (voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE) * 100.0f;
	    // Implementação manual de clamp
    if (percentage < 0.0f) percentage = 0.0f;
    if (percentage > 100.0f) percentage = 100.0f;
	return percentage;
}

std::string Battery::getStatus(float voltage) {
	//float voltage = getVoltage();
	if (voltage >= 12.0f)
		return "FULL";
	else if (voltage >= 11.1f)
		return "GOOD";
	else if (voltage >= 10.2f)
		return "LOW";
	else
		return "CRITICAL";
}

std::vector<float> Battery::get_cell_voltages(float total_voltage) {
    return std::vector<float>(3, total_voltage / 3);
}

std::map<std::string, float> Battery::get_battery_info() {
    float voltage = getVoltage();
    float percentage = getPercentage();
    int adc_value = read_adc();
    float adc_voltage = (adc_value * ADC_REF) / ADC_MAX;
    std::vector<float> cell_voltages = get_cell_voltages(voltage);

    std::map<std::string, float> info = {
        {"voltage", voltage},
        {"percentage", percentage},
        {"raw_adc", static_cast<float>(adc_value)},
        {"adc_voltage", adc_voltage},
        {"cell_voltages", cell_voltages[0]} // Simplified representation
    };

    return info;
}

////------------MAIN

int main() {
    try {
        Battery battery;
        std::cout << "Monitor de Bateria 18650 3S\n";
        std::cout << "Pressione Ctrl+C para sair\n";

        while (true) {
            auto info = battery.get_battery_info();
            std::cout << "Valor ADC: " << info["raw_adc"] << "\n";
            std::cout << "Tensão ADC: " << info["adc_voltage"] << "V\n";
            std::cout << "Tensão Total: " << info["voltage"] << "V\n";
            std::cout << "Tensão por célula: " << info["cell_voltages"] << "V\n";
            std::cout << "Bateria: " << info["percentage"] << "%\n";
            std::cout << "Status: " << battery.getStatus(info["voltage"]) << "\n";
            std::cout << "--------------------\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
    return 0;
}