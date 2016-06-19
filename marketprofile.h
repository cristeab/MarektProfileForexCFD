#ifndef MARKET_PROFILE_H_
#define MARKET_PROFILE_H_

#include <QVector>
#include <QMap>
#include <QDateTime>
#include "qcustomplot.h"

class MarketProfile : public QCustomPlot {
public:
    struct Data
    {
        Data() : open(0), high(0), low(0), close(0), volume(0) {}
        double open;
        double high;
        double low;
        double close;
        int volume;
    };
    explicit MarketProfile(QWidget *parent);
    bool setBackgroudColor(int red, int green, int blue);
    bool setLiteralColor(int red, int green, int blue);
    bool setXLabel(const QString &label);
    bool setYLabel(const QString &label);
    bool setLabelColor(int red, int green, int blue);
    void display(const QMap<QDateTime, MarketProfile::Data> &data);
private:
    enum {MAP_RESOLUTION = 10};
    void process(const QVector<double> &upper, const QVector<double> &lower,
                    const QDate &currentDate, bool dump = false) {
        _tickVectorLabels.push_back(currentDate.toString("MMM d yyyy"));
        computeLiteralHeight(upper, lower);
        initLiteralMatrix(upper, lower);
        if (dump) {
            dumpLiteralMatrix();
        }
        processCurrentDay();
    }
    void dumpLiteralMatrix();
    void computeLiteralHeight(const QVector<double> &upper, const QVector<double> &lower);
    void initLiteralMatrix(const QVector<double> &upper, const QVector<double> &lower);
    void processCurrentDay();
    void findMinMax(double &min, double &max, const QVector<double> &upper,
                    const QVector<double> &lower);
    char getLiteralAtIndex(int index) {
        char out = _currentLiteral;
        for (int n = 1; n <= index; ++n) {
            ++out;
            if (out > 'Z') {
                out = 'A';
            }
        }
        return out;
    }
    void incrementCurrentLiteral() {
        ++_currentLiteral;
        if (_currentLiteral > 'Z') {
            _currentLiteral = 'A';
        }
    }
    bool isValidColor(int val) {
        return ((0 <= val) && (255 >= val));
    }

    void displayItem();
    double _letterHeight;
    char _currentLiteral;
    static const char _emptyChar;
    QVector<QVector<char> > _literalMatrix;
    double _yMin;
    double _yMax;
    QVector<QString> _item;
    double _xPos;
    QFont _currentFont;
    double _currentYMin;
    QVector<double> _tickVector;
    QVector<QString> _tickVectorLabels;
    QColor _literalColor;
    QColor _labelColor;
};

#endif
