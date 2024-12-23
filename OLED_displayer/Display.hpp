#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <array>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

# ifdef SKIP_DEPENDENCY
# else
#  include <linux/i2c-dev.h>
# endif



# define DISPLAY_ADDR 0x3C
# define WIDTH 128
# define HEIGHT 32
# define PAGE_AM 4

// Addresses to write data in
# define CMD_ADD 0x00
# define PXL_ADD 0x40

// Commands
# define DISPLAY_OFF 0xAE
# define DISPLAY_ON 0xAF
# define SET_CONTRAST 0x81
# define SET_MULTIPLEX_RATIO 0xA8
# define SET_MEM_ADDR_MODE 0x20
# define DISPLAY_START_LINE 0x40
# define SEG_REMAP_LEFT 0xA0
# define SEG_REMAP_RIGHT 0xA1
# define COM_SCAN_UP 0xC0
# define COM_SCAN_DOWN 0xC8
# define COM_PINS_CONFIG 0xDA
# define CLOCK_FREQUENCY 0xD5
# define CHARGE_PUMP 0x8D
# define SET_PAGE_NO 0xB0
# define NORMAL_DISPLAY 0xA6
# define INVERSE_DISPLAY 0xA7

class	Display
{
	private:
		// CONST CLASS RESOURCES
		enum MEM_ADD_MODE
		{
			HORIZONTAL,
			VERTICAL,
			PAGE,
			INVALID
		};
		static const std::map<char, std::array<unsigned char, 8> >	_charBitmaps;

		//ATTRIBUTES
		int		_fd;
		std::array<unsigned char, PAGE_AM*WIDTH + 1>	_buffer;

		//MEMBER FUNCTIONS
		Display(const Display& other);
		Display&	operator=(const Display& other);

		void	_initDisplay(void);
		void	_initBuffer(void);
		void	_clearBuffer(void);
		void	_fillBuffer(void);
		void	_resetPrintPos(void);
		void	_putChar(const char c, int x, int line);
		void	_writeCmd(unsigned char data) const;
	
	public:

		Display();
		~Display();

		void	setPixel(int x, int y);
		void	unsetPixel(int x, int y);
		void	putText(std::string text, int x, int line);
		void	updateDisplay(void);
		//void	putImage(std::array<std::array<unsigned char, 16>, 16> img, int size, int x, int y);

		class DisplayException: public std::exception
		{
			private:
				std::string	_message;
			public:
				DisplayException(std::string message);
				~DisplayException();
				const char*	what() const throw();
		};

		//void	invert(void); //temp
};

#endif
