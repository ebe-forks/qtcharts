/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DECLARATIVECHART_H
#define DECLARATIVECHART_H

#include <QtCore/QtGlobal>
#include <QDeclarativeItem>
#include <qchart.h>
#include <QAxis>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// TODO: Derive from QChart for easier definition of properties?
class DeclarativeChart : public QDeclarativeItem
// TODO: for QTQUICK2: extend QQuickPainterItem instead
//class DeclarativeChart : public QQuickPaintedItem, public Chart
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme)
    Q_PROPERTY(Animation animationOptions READ animationOptions WRITE setAnimationOptions)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(Legend legend READ legend WRITE setLegend)
    Q_PROPERTY(QAxis *axisX READ axisX)
    Q_PROPERTY(QAxis *axisY READ axisY)
    // TODO: how to define axis labels? This is not very convenient
    Q_PROPERTY(QVariantList axisXLabels READ axisXLabels WRITE setAxisXLabels)
    Q_PROPERTY(int count READ count)
    Q_ENUMS(Animation)
    Q_ENUMS(Theme)
    Q_ENUMS(Legend)
    Q_ENUMS(SeriesType)

public:
    // duplicating enums from QChart to make the QML api namings 1-to-1 with the C++ api
    enum Theme {
        ChartThemeLight = 0,
        ChartThemeBlueCerulean,
        ChartThemeDark,
        ChartThemeBrownSand,
        ChartThemeBlueNcs,
        ChartThemeHighContrast,
        ChartThemeBlueIcy
    };

    enum Animation {
        NoAnimation = 0x0,
        GridAxisAnimations = 0x1,
        SeriesAnimations =0x2,
        AllAnimations = 0x3
    };

    enum Legend {
        LegendDisabled = 0,
        LegendTop,
        LegendBottom,
        LegendLeft,
        LegendRight
    };

    enum SeriesType {
        SeriesTypeLine,
        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypeGroupedBar,
        SeriesTypePie,
        SeriesTypeScatter,
        SeriesTypeSpline
    };

public:
    DeclarativeChart(QDeclarativeItem *parent = 0);
    ~DeclarativeChart();

public: // From QDeclarativeItem/QGraphicsItem
    void childEvent(QChildEvent *event);
    void componentComplete();
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public:
    void setTheme(DeclarativeChart::Theme theme);
    DeclarativeChart::Theme theme();
    void setAnimationOptions(DeclarativeChart::Animation animations);
    DeclarativeChart::Animation animationOptions();
    void setTitle(QString title) {m_chart->setTitle(title);}
    QString title() { return m_chart->title();}
    void setLegend(DeclarativeChart::Legend legend);
    DeclarativeChart::Legend legend();
    QAxis *axisX();
    QAxis *axisY();
    QVariantList axisXLabels();
    void setAxisXLabels(QVariantList list);
    int count();
    Q_INVOKABLE QAbstractSeries *series(int index);
    Q_INVOKABLE QAbstractSeries *series(QString seriesName);
    Q_INVOKABLE QAbstractSeries *createSeries(DeclarativeChart::SeriesType type, QString name = "");

public:
    // Extending QChart with DeclarativeChart is not possible because QObject does not support
    // multi inheritance, so we now have a QChart as a member instead
    QChart *m_chart;
    Legend m_legend;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVECHART_H