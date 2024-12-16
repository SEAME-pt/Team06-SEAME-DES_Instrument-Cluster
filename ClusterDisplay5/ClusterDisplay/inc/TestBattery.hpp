#ifndef TESTBATTERY_HPP
# define TESTBATTERY_HPP

# include <mutex>
# include <QThread>
# include <QTimer>

class TestBattery: public QObject
{
    Q_OBJECT
	public:
		TestBattery();
		~TestBattery();

        float	getPercentage(void);

	private:
        float       m_percentage;
		std::mutex	percentageMutex;
        QTimer*     m_timer;
        void		_updatePercentage(void);
};

#endif // TESTBATTERY_HPP
