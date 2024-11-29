
#include "Display.hpp"

std::map<char, std::array<unsigned char, 8> > Display::_charBitmaps = {
	{' ', {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }},
	{'!', {0x00, 0x00, 0x5f, 0x5f, 0x00, 0x00, 0x00, 0x00, }},
	{',', {0x00, 0x00, 0xe0, 0x60, 0x00, 0x00, 0x00, 0x00, }},
	{'-', {0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, }},
	{'.', {0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, }},
	{'0', {0x3e, 0x7f, 0x71, 0x59, 0x4d, 0x7f, 0x3e, 0x00, }},
	{'1', {0x40, 0x42, 0x7f, 0x7f, 0x40, 0x40, 0x00, 0x00, }},
	{'2', {0x62, 0x73, 0x59, 0x49, 0x6f, 0x66, 0x00, 0x00, }},
	{'3', {0x22, 0x63, 0x49, 0x49, 0x7f, 0x36, 0x00, 0x00, }},
	{'4', {0x18, 0x1c, 0x16, 0x53, 0x7f, 0x7f, 0x50, 0x00, }},
	{'5', {0x27, 0x67, 0x45, 0x45, 0x7d, 0x39, 0x00, 0x00, }},
	{'6', {0x3c, 0x7e, 0x4b, 0x49, 0x79, 0x30, 0x00, 0x00, }},
	{'7', {0x03, 0x03, 0x71, 0x79, 0x0f, 0x07, 0x00, 0x00, }},
	{'8', {0x36, 0x7f, 0x49, 0x49, 0x7f, 0x36, 0x00, 0x00, }},
	{'9', {0x06, 0x4f, 0x49, 0x69, 0x3f, 0x1e, 0x00, 0x00, }},
	{':', {0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, }},
	{'?', {0x02, 0x03, 0x51, 0x59, 0x0f, 0x06, 0x00, 0x00, }},
	{'A', {0x7c, 0x7e, 0x13, 0x13, 0x7e, 0x7c, 0x00, 0x00, }},
	{'B', {0x41, 0x7f, 0x7f, 0x49, 0x49, 0x7f, 0x36, 0x00, }},
	{'C', {0x1c, 0x3e, 0x63, 0x41, 0x41, 0x63, 0x22, 0x00, }},
	{'D', {0x41, 0x7f, 0x7f, 0x41, 0x63, 0x3e, 0x1c, 0x00, }},
	{'E', {0x41, 0x7f, 0x7f, 0x49, 0x5d, 0x41, 0x63, 0x00, }},
	{'F', {0x41, 0x7f, 0x7f, 0x49, 0x1d, 0x01, 0x03, 0x00, }},
	{'G', {0x1c, 0x3e, 0x63, 0x41, 0x51, 0x73, 0x72, 0x00, }},
	{'H', {0x7f, 0x7f, 0x08, 0x08, 0x7f, 0x7f, 0x00, 0x00, }},
	{'I', {0x00, 0x41, 0x7f, 0x7f, 0x41, 0x00, 0x00, 0x00, }},
	{'J', {0x30, 0x70, 0x40, 0x41, 0x7f, 0x3f, 0x01, 0x00, }},
	{'K', {0x41, 0x7f, 0x7f, 0x08, 0x1c, 0x77, 0x63, 0x00, }},
	{'L', {0x41, 0x7f, 0x7f, 0x41, 0x40, 0x60, 0x70, 0x00, }},
	{'M', {0x7f, 0x7f, 0x06, 0x0c, 0x06, 0x7f, 0x7f, 0x00, }},
	{'N', {0x7f, 0x7f, 0x06, 0x0c, 0x18, 0x7f, 0x7f, 0x00, }},
	{'O', {0x1c, 0x3e, 0x63, 0x41, 0x63, 0x3e, 0x1c, 0x00, }},
	{'P', {0x41, 0x7f, 0x7f, 0x49, 0x09, 0x0f, 0x06, 0x00, }},
	{'Q', {0x1e, 0x3f, 0x21, 0x71, 0x7f, 0x5e, 0x00, 0x00, }},
	{'R', {0x41, 0x7f, 0x7f, 0x09, 0x19, 0x7f, 0x66, 0x00, }},
	{'S', {0x22, 0x67, 0x4d, 0x59, 0x73, 0x22, 0x00, 0x00, }},
	{'T', {0x03, 0x41, 0x7f, 0x7f, 0x41, 0x03, 0x00, 0x00, }},
	{'U', {0x3f, 0x7f, 0x40, 0x40, 0x7f, 0x3f, 0x00, 0x00, }},
	{'V', {0x1f, 0x3f, 0x60, 0x60, 0x3f, 0x1f, 0x00, 0x00, }},
	{'W', {0x7f, 0x7f, 0x30, 0x18, 0x30, 0x7f, 0x7f, 0x00, }},
	{'X', {0x63, 0x77, 0x1c, 0x08, 0x1c, 0x77, 0x63, 0x00, }},
	{'Y', {0x07, 0x4f, 0x78, 0x78, 0x4f, 0x07, 0x00, 0x00, }},
	{'Z', {0x67, 0x73, 0x59, 0x4d, 0x67, 0x73, 0x00, 0x00, }},
};

std::array<std::array<unsigned char, 16>, 16>	Display::_faceBitmaps0 = 
{{	
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,1,1,0,1,0,0,0,0,1,0,1,1,0,0},
	{0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0}
}};

std::array<std::array<unsigned char, 16>, 16>   Display::_faceBitmaps1 =
{{
        {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
        {0,0,1,1,0,1,0,0,0,0,1,0,1,1,0,0},
        {0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1},
        {1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
        {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0},
        {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
        {0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0},
        {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
}};

Display::Display(): faces{Display::_faceBitmaps0, Display::_faceBitmaps1}
{
	std::cout << "Opening connection I2C..." << std::endl;
	_fd = open("/dev/i2c-1", O_RDWR);
	if (_fd < 0)
		throw (DisplayException("Error opening I2C connection."));

	std::cout << "Configuring display address.." << std::endl;
	if (ioctl(_fd, I2C_SLAVE, DISPLAY_ADDR) < 0)
		throw (DisplayException("Error configuring display address."));
	

	_initDisplay();
}

Display::Display(std::string _testConstructor)
{
	_fd = STDOUT_FILENO;
	_initDisplay();
}
Display::Display(const Display& other): _fd(other._fd), _buffer(other._buffer) {}
Display&	Display::operator=(const Display& other)
{
	if (this != &other)
	{
		_fd = other._fd;
		_buffer = other._buffer;
	}
	return (*this);
}

Display::~Display()
{
	if (_fd > 0)
		close(_fd);
}


void	Display::_initDisplay(void)
{
	_writeCmd(DISPLAY_OFF);
	_writeCmd(SET_CONTRAST);
	_writeCmd(0xFF);

	_writeCmd(SET_MULTIPLEX_RATIO);
	_writeCmd(31);

	_writeCmd(SET_MEM_ADDR_MODE);
	_writeCmd(HORIZONTAL);

	_writeCmd(DISPLAY_START_LINE);
	_writeCmd(SEG_REMAP_RIGHT);
	_writeCmd(COM_SCAN_DOWN);

	_writeCmd(COM_PINS_CONFIG);
	_writeCmd(0x02);

	_writeCmd(0xD5);
	_writeCmd(0x80);

	_writeCmd(0x8D);
	_writeCmd(0x14);

	_resetPrintPos();
	_initBuffer();
	updateDisplay();
	
	_writeCmd(NORMAL_DISPLAY);
	_writeCmd(DISPLAY_ON);

}

void	Display::_initBuffer(void)
{
	_buffer[0] = PXL_ADD;
	_clearBuffer();
}
void	Display::_clearBuffer(void) {std::fill(_buffer.begin() + 1, _buffer.end(), 0);}
void	Display::_fillBuffer(void) {std::fill(_buffer.begin() + 1, _buffer.end(), 0xFF);}
void	Display::_resetPrintPos(void)
{
	_writeCmd(SET_PAGE_NO | 0);
	_writeCmd(0x00);
	_writeCmd(0x10);
}

void	Display::updateDisplay(void)
{
	_resetPrintPos();
	write(_fd, _buffer.data(), _buffer.size());
}

void	Display::_writeCmd(unsigned char data) const
{
	unsigned char	buffer[2];
	buffer[0] = CMD_ADD;
	buffer[1] = data;
	write(_fd, buffer, 2);
}

void	Display::setPixel(int x, int y) {_buffer[y/8*WIDTH+x+1] |= 1<<(y%8);}
void	Display::unsetPixel(int x, int y) {_buffer[y/8*WIDTH+x+1] &= ~(1<<(y%8));}

void	Display::putText(std::string text, int x, int y)
{
	for (int i=0; i<text.size(); i++)
		putChar(text[i], (i*8)+x, y);
}
void	Display::putChar(char c, int x, int y)
{
	std::array<unsigned char, 8>	bitmap = Display::_charBitmaps[c];
	for (int i=0; i<8; i++)
		_buffer[y/8*WIDTH+x+i+1] = bitmap[i];
}

void	Display::putImage(std::array<std::array<unsigned char, 16>, 16> img, int size, int x, int y)
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			if (img[i][j])
				setPixel(x+j, y+i);
			else
				unsetPixel(x+j, y+i);
		}
	}
}


Display::DisplayException::DisplayException(std::string message)
: _message(message) {}
Display::DisplayException::~DisplayException(){}
const char* Display::DisplayException::what() const throw()
{return (_message.c_str());}

/*void	Display::invert(void)
{
	std::map<char, std::array<unsigned char, 8> >::iterator	it1;
	for (it1=_charBitmaps.begin(); it1!=_charBitmaps.end(); it1++)
	{
		std::cout << "{'" << it1->first << "', {";

		for (int i=0; i<8; i++)
		{
			unsigned char	byte = 0;
			std::array<unsigned char, 8>::reverse_iterator	it2;
			for (it2=it1->second.rbegin(); it2!=it1->second.rend(); it2++)
			{
				if (1<<(7-i) & *it2)
				{
					byte |= 1<<(7 - (it2 - it1->second.rbegin()));
				}
			}
			std::cout << "0x" << std::hex << std::setfill ('0') << std::setw (2) << static_cast<int>(byte) << ", ";

		}
		std::cout << "}," << std::endl;
	}
}*/