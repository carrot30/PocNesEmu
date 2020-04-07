#pragma once

#include <cstdint>
#include <memory>

#include "INesPpu.h"


class PPU_2C02 final : public INesPpu {
public:
	PPU_2C02() : m_size(8) {}


	void reset() override;
	void tick() override;


	// From IBusMaster
	void connectBus(std::shared_ptr<IBus<uint16_t, uint8_t>> bus) override;
	//	--------------


	// From IBusSlave
	inline const uint16_t size() override { return m_size; }
	uint8_t read(uint16_t address) override;
	void write(uint16_t address, uint8_t data) override;
	// --------------

private:
	// From IBusMaster
	inline uint8_t readFrom(uint16_t address) override {
		return m_bus->read(address);
	}

	inline void writeTo(uint16_t address, uint8_t data) override {
		m_bus->write(address, data);
	}
	//	--------------

private:
	bool m_busConnected = false;
	uint16_t m_size { 0x8 };
	uint8_t m_tempData = 0x00;
	uint8_t m_pallette[0x20];

};
