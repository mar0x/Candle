// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef GCODEDRAWER_H
#define GCODEDRAWER_H

#include <QObject>
#include <QVector3D>
#include "parser/linesegment.h"
#include "parser/gcodeviewparse.h"
#include "shaderdrawable.h"

class GcodeDrawer : public QObject, public ShaderDrawable
{
    Q_OBJECT
public:
    enum GrayscaleCode { S, Z };
    enum DrawMode { Vectors, Raster };

    explicit GcodeDrawer(GcodeViewParse* viewParser);

    void update();
    void update(int index);
    void update(const QList<int>& indexes);
    bool updateData() override;

    QVector3D getSizes() const override;
    QVector3D getMinimumExtremes() const override;
    QVector3D getMaximumExtremes() const override;

    GcodeViewParse* viewParser();

    bool simplify() const;
    void setSimplify(bool simplify);

    double simplifyPrecision() const;
    void setSimplifyPrecision(double simplifyPrecision);

    bool geometryUpdated() const;

    const QColor& colorNormal() const;
    void setColorNormal(const QColor &colorNormal);

    const QColor& colorHighlight() const;
    void setColorHighlight(const QColor &colorHighlight);

    const QColor& colorZMovement() const;
    void setColorZMovement(const QColor &colorZMovement);

    const QColor& colorDrawn() const;
    void setColorDrawn(const QColor &colorDrawn);

    const QColor& colorStart() const;
    void setColorStart(const QColor &colorStart);

    const QColor& colorEnd() const;
    void setColorEnd(const QColor &colorEnd);

    bool getIgnoreZ() const;
    void setIgnoreZ(bool ignoreZ);

    bool getGrayscaleSegments() const;
    void setGrayscaleSegments(bool grayscaleSegments);

    GrayscaleCode grayscaleCode() const;
    void setGrayscaleCode(const GrayscaleCode &grayscaleCode);

    int grayscaleMin() const;
    void setGrayscaleMin(int grayscaleMin);

    int grayscaleMax() const;
    void setGrayscaleMax(int grayscaleMax);

    DrawMode drawMode() const;
    void setDrawMode(const DrawMode &drawMode);

signals:

public slots:

private slots:
    void onTimerVertexUpdate();

private:
    GcodeViewParse* m_viewParser;

    DrawMode m_drawMode;

    bool m_simplify;
    double m_simplifyPrecision;
    bool m_ignoreZ;
    bool m_grayscaleSegments;
    GrayscaleCode m_grayscaleCode;
    int m_grayscaleMin;
    int m_grayscaleMax;

    QColor m_colorNormal;
    QColor m_colorDrawn;
    QColor m_colorHighlight;
    QColor m_colorZMovement;
    QColor m_colorStart;
    QColor m_colorEnd;

    QTimer m_timerVertexUpdate;

    QImage m_image;
    QList<int> m_indexes;
    bool m_geometryUpdated;

    bool prepareVectors();
    bool updateVectors();
    bool prepareRaster();
    bool updateRaster();

    int getSegmentType(const LineSegment& segment) const;
    QVector3D getSegmentColorVector(const LineSegment& segment) const;
    QColor getSegmentColor(const LineSegment& segment) const;
    void setImagePixelColor(QImage &image, double x, double y, QRgb color) const;
};

#endif // GCODEDRAWER_H
