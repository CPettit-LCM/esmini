#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RoadManager.hpp"
#include <vector>
#include <stdexcept>

using namespace roadmanager;

#define TRIG_ERR_MARGIN 0.001

//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Polynomial //////////
//////////////////////////////////////////////////////////////////////

class PolynomialTestFixture: public testing::Test
{
    public:
        PolynomialTestFixture();
        PolynomialTestFixture(double a, double b, double c, double d, double p_scale);
        virtual ~PolynomialTestFixture();
    protected:
        Polynomial poly;
};


PolynomialTestFixture::PolynomialTestFixture()
{
}

PolynomialTestFixture::PolynomialTestFixture(double a, double b, double c, double d, double p_scale)
{
}

PolynomialTestFixture::~PolynomialTestFixture()
{
}

TEST_F(PolynomialTestFixture, TestConstructorEmpty)
{
    ASSERT_EQ(0, poly.GetA());
    ASSERT_EQ(0, poly.GetB());
    ASSERT_EQ(0, poly.GetC());
    ASSERT_EQ(0, poly.GetD());
    ASSERT_EQ(1, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestConstructorArgument)
{
    Polynomial poly = Polynomial(1,-2,3,-4);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
    ASSERT_EQ(1, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestConstructorArgumentPscale)
{
    Polynomial poly = Polynomial(1,-2,3,-4,2);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
    ASSERT_EQ(2, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestSetGet)
{
    poly.Set(1,-2,3,-4);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
    ASSERT_EQ(1, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestSetGetPscale)
{
    poly.Set(1,-2,3,-4, 2);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
    ASSERT_EQ(2, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestSetGetIndividual)
{
    poly.SetA(1);
    poly.SetB(-2);
    poly.SetC(3);
    poly.SetD(-4);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
}

class PolynomialTestEvaluateEmptyParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_empty;
};

TEST_P(PolynomialTestEvaluateEmptyParametrized, TestEvaluateEmptyConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    poly_empty.SetA(1);
    poly_empty.SetB(-2);
    poly_empty.SetC(3);
    poly_empty.SetD(-4);
    ASSERT_EQ(poly_empty.Evaluate(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateParamEmpty, PolynomialTestEvaluateEmptyParametrized, testing::Values(
                                                std::make_tuple(2,-23),
                                                std::make_tuple(0, 1)));

class PolynomialTestEvaluateArgumentParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_argument{1,-2,3,-4,2};
};

TEST_P(PolynomialTestEvaluateArgumentParametrized, TestEvaluateArgumentConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    ASSERT_EQ(poly_argument.Evaluate(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateParamArgument, PolynomialTestEvaluateArgumentParametrized, testing::Values(
                                                std::make_tuple(2,-215),
                                                std::make_tuple(0, 1)));


class PolynomialTestEvaluatePrimEmptyParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_empty;
};

TEST_P(PolynomialTestEvaluatePrimEmptyParametrized, TestEvaluatePrimEmptyConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    poly_empty.SetA(1);
    poly_empty.SetB(-2);
    poly_empty.SetC(3);
    poly_empty.SetD(-4);
    ASSERT_EQ(poly_empty.EvaluatePrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimParamEmpty, PolynomialTestEvaluatePrimEmptyParametrized, testing::Values(
                                                std::make_tuple(2,-38),
                                                std::make_tuple(0, -2)));

class PolynomialTestEvaluatePrimArgumentParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_argument{1,-2,3,-4,2};
};

TEST_P(PolynomialTestEvaluatePrimArgumentParametrized, TestEvaluatePrimArgumentConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    ASSERT_EQ(poly_argument.EvaluatePrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimParamArgument, PolynomialTestEvaluatePrimArgumentParametrized, testing::Values(
                                                std::make_tuple(2,-170),
                                                std::make_tuple(0, -2)));

class PolynomialTestEvaluatePrimPrimEmptyParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_empty;
};

TEST_P(PolynomialTestEvaluatePrimPrimEmptyParametrized, TestEvaluatePrimPrimEmptyConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    poly_empty.SetA(1);
    poly_empty.SetB(-2);
    poly_empty.SetC(3);
    poly_empty.SetD(-4);
    ASSERT_EQ(poly_empty.EvaluatePrimPrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimPrimParamEmpty, PolynomialTestEvaluatePrimPrimEmptyParametrized, testing::Values(
                                                std::make_tuple(2,-42),
                                                std::make_tuple(0, 6)));

class PolynomialTestEvaluatePrimPrimArgumentParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_argument{1,-2,3,-4,2};
};

TEST_P(PolynomialTestEvaluatePrimPrimArgumentParametrized, TestEvaluatePrimPrimArgumentConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    ASSERT_EQ(poly_argument.EvaluatePrimPrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimPrimParamArgument, PolynomialTestEvaluatePrimPrimArgumentParametrized, testing::Values(
                                                std::make_tuple(2,-90),
                                                std::make_tuple(0, 6)));

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> OSIPoints //////////
//////////////////////////////////////////////////////////////////////

class OSIPointsTestFixture: public testing::Test
{
    public:
        OSIPointsTestFixture();
        OSIPointsTestFixture(std::vector<double> s, std::vector<double> x, std::vector<double> y, std::vector<double> z, std::vector<double> h);
        virtual ~OSIPointsTestFixture();
    protected:
        OSIPoints osi_points;
};

OSIPointsTestFixture::OSIPointsTestFixture()
{
}

OSIPointsTestFixture::OSIPointsTestFixture(std::vector<double> s, std::vector<double> x, std::vector<double> y, std::vector<double> z, std::vector<double> h)
{
}

OSIPointsTestFixture::~OSIPointsTestFixture()
{
}

TEST_F(OSIPointsTestFixture, TestConstructorEmpty)
{
    ASSERT_EQ(0, osi_points.GetS().size());
    ASSERT_EQ(0, osi_points.GetX().size());
    ASSERT_EQ(0, osi_points.GetY().size());
    ASSERT_EQ(0, osi_points.GetZ().size());
    ASSERT_EQ(0, osi_points.GetH().size());
}

TEST_F(OSIPointsTestFixture, TestConstructorArgument)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points = OSIPoints(s, x, y, z, h);

    std::vector<double> s_expected = osi_points.GetS();
    std::vector<double> x_expected = osi_points.GetX();
    std::vector<double> y_expected = osi_points.GetY();
    std::vector<double> z_expected = osi_points.GetZ();
    std::vector<double> h_expected = osi_points.GetH();

    ASSERT_EQ(s, s_expected);
    ASSERT_EQ(x, x_expected);
    ASSERT_EQ(y, y_expected);
    ASSERT_EQ(z, z_expected);
    ASSERT_EQ(h, h_expected);
}

TEST_F(OSIPointsTestFixture, TestSetGet)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};
    
    osi_points.Set(s,x,y,z,h);

    std::vector<double> s_expected = osi_points.GetS();
    std::vector<double> x_expected = osi_points.GetX();
    std::vector<double> y_expected = osi_points.GetY();
    std::vector<double> z_expected = osi_points.GetZ();
    std::vector<double> h_expected = osi_points.GetH();

    ASSERT_EQ(s, s_expected);
    ASSERT_EQ(x, x_expected);
    ASSERT_EQ(y, y_expected);
    ASSERT_EQ(z, z_expected);
    ASSERT_EQ(h, h_expected);
}

TEST_F(OSIPointsTestFixture, TestGetFromIdxEmpty)
{
    ASSERT_THROW(osi_points.GetXfromIdx(-1), std::runtime_error);
    ASSERT_THROW(osi_points.GetYfromIdx(-1), std::runtime_error);
    ASSERT_THROW(osi_points.GetZfromIdx(-1), std::runtime_error);
    ASSERT_THROW(osi_points.GetXfromIdx(0), std::runtime_error);
    ASSERT_THROW(osi_points.GetYfromIdx(0), std::runtime_error);
    ASSERT_THROW(osi_points.GetZfromIdx(0), std::runtime_error);
    ASSERT_THROW(osi_points.GetXfromIdx(1), std::runtime_error);
    ASSERT_THROW(osi_points.GetYfromIdx(1), std::runtime_error);
    ASSERT_THROW(osi_points.GetZfromIdx(1), std::runtime_error);
}

TEST_F(OSIPointsTestFixture, TestGetFromIdx)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points = OSIPoints(s, x, y, z, h);

    ASSERT_EQ(osi_points.GetXfromIdx(0), (double)0);
    ASSERT_EQ(osi_points.GetXfromIdx(1), (double)-1);
    ASSERT_EQ(osi_points.GetXfromIdx(2), (double)2);

    ASSERT_EQ(osi_points.GetYfromIdx(0), (double)0);
    ASSERT_EQ(osi_points.GetYfromIdx(1), (double)-1);
    ASSERT_EQ(osi_points.GetYfromIdx(2), (double)2);

    ASSERT_EQ(osi_points.GetZfromIdx(0), (double)0);
    ASSERT_EQ(osi_points.GetZfromIdx(1), (double)-1);
    ASSERT_EQ(osi_points.GetZfromIdx(2), (double)2);
}

TEST_F(OSIPointsTestFixture, TestGetNumOfOSIPointsCorrupt)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points = OSIPoints(s, x, y, z, h);
    ASSERT_THROW(osi_points.GetNumOfOSIPoints(), std::runtime_error);
}

TEST_F(OSIPointsTestFixture, TestGetNumOfOSIPoints)
{
    ASSERT_EQ(osi_points.GetNumOfOSIPoints(), 0);
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points_second = OSIPoints(s, x, y, z, h);
    ASSERT_EQ(osi_points_second.GetNumOfOSIPoints(), 3);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Line (Geometry) //////////
//////////////////////////////////////////////////////////////////////

class LineGeomTestFixture: public testing::Test
{
    public:
        LineGeomTestFixture();
        LineGeomTestFixture(double s, double x, double y, double hdg, double length);
        virtual ~LineGeomTestFixture();
    protected:
        Line line;
};

LineGeomTestFixture::LineGeomTestFixture()
{
}

LineGeomTestFixture::LineGeomTestFixture(double s, double x, double y, double hdg, double length)
{
}

LineGeomTestFixture::~LineGeomTestFixture()
{
}

TEST_F(LineGeomTestFixture, TestConstructorArgument)
{
    ASSERT_EQ(0, line.GetS());
    ASSERT_EQ(0, line.GetX());
    ASSERT_EQ(0, line.GetY());
    ASSERT_EQ(0, line.GetHdg());
    ASSERT_EQ(0, line.GetLength());
    EXPECT_EQ(line.GetType(), Geometry::GEOMETRY_TYPE_UNKNOWN);

    Line line_second = Line(2, -1, 1, 5*M_PI, 4);
    ASSERT_EQ(2, line_second.GetS());
    ASSERT_EQ(-1, line_second.GetX());
    ASSERT_EQ(1, line_second.GetY());
    ASSERT_EQ(M_PI, line_second.GetHdg());
    ASSERT_EQ(4, line_second.GetLength());
    EXPECT_EQ(line_second.GetType(), Geometry::GEOMETRY_TYPE_LINE);

    Line line_third = Line(2, -1, 1, -5*M_PI, 4);
    ASSERT_EQ(2, line_third.GetS());
    ASSERT_EQ(-1, line_third.GetX());
    ASSERT_EQ(1, line_third.GetY());
    ASSERT_EQ(M_PI, line_third.GetHdg());
    ASSERT_EQ(4, line_third.GetLength());
    EXPECT_EQ(line_third.GetType(), Geometry::GEOMETRY_TYPE_LINE);
}

TEST_F(LineGeomTestFixture, TestEvaluateCurvatureDS)
{
    ASSERT_EQ(line.EvaluateCurvatureDS(0), 0.0);
    ASSERT_EQ(line.EvaluateCurvatureDS(10), 0.0);
    ASSERT_EQ(line.EvaluateCurvatureDS(100), 0.0);
    ASSERT_EQ(line.EvaluateCurvatureDS(1000), 0.0);
}


class LineGeomTestEvaluateDsEmptyConstructor: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Line line;
};

TEST_P(LineGeomTestEvaluateDsEmptyConstructor, TestLineGeomEvaluateDsEmpty)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = line.GetX();
    double my_y = line.GetY();
    double my_h = line.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    line.EvaluateDS(std::get<0>(tuple), x, y, h);
    ASSERT_EQ(*x, std::get<1>(tuple));
    ASSERT_EQ(*y, std::get<2>(tuple));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateDsEmptyParam, LineGeomTestEvaluateDsEmptyConstructor, testing::Values(
                                                std::make_tuple(0, 0, 0, 0),
                                                std::make_tuple(1, 1, 0, 0),
                                                std::make_tuple(100, 100, 0, 0)));

class LineGeomTestEvaluateDsArgumentConstructor: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Line line{2.0, -1.0, 1.0, 5*M_PI, 4.0};
};

TEST_P(LineGeomTestEvaluateDsArgumentConstructor, TestLineGeomEvaluateDsArgument)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = line.GetX();
    double my_y = line.GetY();
    double my_h = line.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    line.EvaluateDS(std::get<0>(tuple), x, y, h);
    ASSERT_EQ(*x, std::get<1>(tuple));
    ASSERT_EQ(*y, std::get<2>(tuple));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateLineDsArgumentParam, LineGeomTestEvaluateDsArgumentConstructor, testing::Values(
                                                std::make_tuple(0.0, -1.0, 1.0, M_PI),
                                                std::make_tuple(1.0, -2.0, 1.0+sin(M_PI), M_PI),
                                                std::make_tuple(100.0, -101.0, 1.0+100*sin(M_PI), M_PI)));

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Arc (Geometry) //////////
//////////////////////////////////////////////////////////////////////

class ArcGeomTestFixture: public testing::Test
{
    public:
        ArcGeomTestFixture();
        ArcGeomTestFixture(double s, double x, double y, double hdg, double length, double curvature);
        virtual ~ArcGeomTestFixture();
    protected:
        Arc arc;
};

ArcGeomTestFixture::ArcGeomTestFixture()
{
}

ArcGeomTestFixture::ArcGeomTestFixture(double s, double x, double y, double hdg, double length, double curvature)
{
}

ArcGeomTestFixture::~ArcGeomTestFixture()
{
}

TEST_F(ArcGeomTestFixture, TestConstructorArgument)
{
    ASSERT_EQ(0.0, arc.GetCurvature());
    EXPECT_EQ(arc.GetType(), Geometry::GEOMETRY_TYPE_UNKNOWN);

    Arc arc_second = Arc(2, -1, 1, 5*M_PI, 4, 5);
    ASSERT_EQ(5.0, arc_second.GetCurvature());
    EXPECT_EQ(arc_second.GetType(), Geometry::GEOMETRY_TYPE_ARC);
}

TEST_F(ArcGeomTestFixture, TestEvaluateCurvatureDS)
{
    ASSERT_EQ(arc.EvaluateCurvatureDS(0), 0.0);
    ASSERT_EQ(arc.EvaluateCurvatureDS(10), 0.0);
    ASSERT_EQ(arc.EvaluateCurvatureDS(100), 0.0);
    ASSERT_EQ(arc.EvaluateCurvatureDS(1000), 0.0);

    Arc arc_second = Arc(2, -1, 1, 5*M_PI, 4, 5);

    ASSERT_EQ(arc_second.EvaluateCurvatureDS(0), 5.0);
    ASSERT_EQ(arc_second.EvaluateCurvatureDS(10), 5.0);
    ASSERT_EQ(arc_second.EvaluateCurvatureDS(100), 5.0);
    ASSERT_EQ(arc_second.EvaluateCurvatureDS(1000), 5.0);
}

TEST_F(ArcGeomTestFixture, TestGetRadius)
{
    Arc arc_second = Arc(2, -1, 1, 5*M_PI, 4, 5);
    ASSERT_EQ(arc_second.GetRadius(), 0.2);

    Arc arc_third = Arc(2, -1, 1, 5*M_PI, 4, -10);
    ASSERT_EQ(arc_third.GetRadius(), 0.1);
}

class ArcGeomTestEvaluateDsCurvPositive: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Arc arc{2.0, -1.0, 1.0, 5*M_PI, 4.0, 1.0};
};

TEST_P(ArcGeomTestEvaluateDsCurvPositive, TestArcGeomEvaluateDsArgument)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = arc.GetX();
    double my_y = arc.GetY();
    double my_h = arc.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    arc.EvaluateDS(std::get<0>(tuple), x, y, h);
    testing::AllOf(testing::Gt(std::get<1>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<1>(tuple)+TRIG_ERR_MARGIN));
    testing::AllOf(testing::Gt(std::get<2>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<2>(tuple)+TRIG_ERR_MARGIN));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateArcDsArgumentParam, ArcGeomTestEvaluateDsCurvPositive, testing::Values(
                                                std::make_tuple(0.0, -1.0, 1.0, M_PI),
                                                std::make_tuple(1.0, -1.0-cos(271), -1.0-sin(271), M_PI+1),
                                                std::make_tuple(90.0, 0, 2, M_PI+90)));

class ArcGeomTestEvaluateDsCurvNegative: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Arc arc{2.0, -1.0, 1.0, 5*M_PI, 4.0, -1.0};
};

TEST_P(ArcGeomTestEvaluateDsCurvNegative, TestArcGeomEvaluateDsArgument)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = arc.GetX();
    double my_y = arc.GetY();
    double my_h = arc.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    arc.EvaluateDS(std::get<0>(tuple), x, y, h);
    testing::AllOf(testing::Gt(std::get<1>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<1>(tuple)+TRIG_ERR_MARGIN));
    testing::AllOf(testing::Gt(std::get<2>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<2>(tuple)+TRIG_ERR_MARGIN));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateArcDsArgumentParam, ArcGeomTestEvaluateDsCurvNegative, testing::Values(
                                                std::make_tuple(0.0, -1.0, 1.0, M_PI),
                                                std::make_tuple(1.0, -1.0-cos(91), 2.0-sin(91), M_PI-1),
                                                std::make_tuple(90.0, -2, 2, M_PI-90)));                                    

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Spiral (Geometry) //////////
//////////////////////////////////////////////////////////////////////





/******************************************
* Test the LineLink class
******************************************/
// Tests the class constructor.
TEST(LaneLinkTest, DefaultConstructor) {
    LaneLink lane_link(UNKNOWN, 0);
    EXPECT_EQ(UNKNOWN, lane_link.GetType());
    EXPECT_EQ(0,lane_link.GetId());
}

/******************************************
* Test the LaneWidth class
******************************************/
// Tests the class constructor.
TEST(LaneWidthTest, DefaultConstructor) {
    LaneWidth lane_width(1, 1, 1, 1, 1);
    EXPECT_EQ(1, lane_width.GetSOffset());
}

/******************************************
* Test the LaneBoundaryOSI class
******************************************/

/******************************************
* Test the LaneRoadMarkTypeLine class
******************************************/
class LaneRoadMarkTypeLineTest :public ::testing::TestWithParam<std::tuple<double,double,double,double,LaneRoadMarkTypeLine::RoadMarkTypeLineRule,double>> {};
// inp: length,space,t_offset,s_offset,rule,width

TEST_P(LaneRoadMarkTypeLineTest, DefaultConstructor) {
    LaneRoadMarkTypeLine lane_roadmarking = LaneRoadMarkTypeLine(
        std::get<0>(GetParam()),
        std::get<1>(GetParam()),
        std::get<2>(GetParam()),
        std::get<3>(GetParam()),
        std::get<4>(GetParam()),
        std::get<5>(GetParam()));

    EXPECT_EQ(lane_roadmarking.GetLength(),std::get<0>(GetParam()));
    EXPECT_EQ(lane_roadmarking.GetSpace(),std::get<1>(GetParam()));
    EXPECT_EQ(lane_roadmarking.GetTOffset(),std::get<2>(GetParam()));
    EXPECT_EQ(lane_roadmarking.GetSOffset(),std::get<3>(GetParam()));

    // Test SetGlobalId method
    // OSI related stuff not implemented yet
    //lane_roadmarking.SetGlobalId();
    //EXPECT_EQ(lane_roadmarking.GetGlobalId(), 0);
}

INSTANTIATE_TEST_CASE_P(LaneRoadMarkTypeLineTests,LaneRoadMarkTypeLineTest,::testing::Values(
    std::make_tuple(100,100,0,0,LaneRoadMarkTypeLine::NO_PASSING,2),
    std::make_tuple(10,10,-1,1,LaneRoadMarkTypeLine::CAUTION,6)));

/******************************************
* Test the LaneRoadMarkType class
******************************************/
class LaneRoadMarkTypeTest : public ::testing::Test {
    protected:
    void SetUp() override { lane_test_0 = new LaneRoadMarkType("test", 0.2); }
    LaneRoadMarkType* lane_test_0;
};

TEST_F(LaneRoadMarkTypeTest, DefaultConstructor) {
    EXPECT_EQ(lane_test_0->GetName(),"test");
    EXPECT_EQ(lane_test_0->GetWidth(),0.2);
}

TEST_F(LaneRoadMarkTypeTest,AddLine) {
    LaneRoadMarkTypeLine * line_0 = new LaneRoadMarkTypeLine(100,100,0,0,LaneRoadMarkTypeLine::NO_PASSING,2);
    lane_test_0->AddLine(line_0);
    EXPECT_EQ(lane_test_0->GetNumberOfRoadMarkTypeLines(), 1);

    // test GetLaneRoadMarkTypeLineByIdx method
    EXPECT_EQ(lane_test_0->GetLaneRoadMarkTypeLineByIdx(0)->GetLength(), line_0->GetLength());
}

/******************************************
* Test the LaneRoadMark class
******************************************/
class LaneRoadMarkTest :public ::testing::TestWithParam<std::tuple<double,LaneRoadMark::RoadMarkType,LaneRoadMark::RoadMarkWeight,LaneRoadMark::RoadMarkColor,LaneRoadMark::RoadMarkMaterial,LaneRoadMark::RoadMarkLaneChange,double,double>> {};
// inp: s_offset,type,weight,color,material,lane_change,width,height

TEST_P(LaneRoadMarkTest, DefaultConstructor) {
    LaneRoadMark lane_test_0 = LaneRoadMark(
        std::get<0>(GetParam()),
        std::get<1>(GetParam()),
        std::get<2>(GetParam()),
        std::get<3>(GetParam()),
        std::get<4>(GetParam()),
        std::get<5>(GetParam()),
        std::get<6>(GetParam()),
        std::get<7>(GetParam()));

    EXPECT_EQ(lane_test_0.GetSOffset(),std::get<0>(GetParam()));
    EXPECT_EQ(lane_test_0.GetType(),std::get<1>(GetParam()));
    EXPECT_EQ(lane_test_0.GetColor(),std::get<3>(GetParam()));
    EXPECT_EQ(lane_test_0.GetWidth(),std::get<6>(GetParam()));
    EXPECT_EQ(lane_test_0.GetHeight(),std::get<7>(GetParam()));

    LaneRoadMarkType * type_test_0 = new LaneRoadMarkType("test", 0.2);
    lane_test_0.AddType(type_test_0);
    EXPECT_EQ(lane_test_0.GetNumberOfRoadMarkTypes(),1);
    EXPECT_EQ(lane_test_0.GetLaneRoadMarkTypeByIdx(0)->GetName(),type_test_0->GetName());
}

INSTANTIATE_TEST_CASE_P(LaneRoadMarkTests,LaneRoadMarkTest,::testing::Values(
    std::make_tuple(0,LaneRoadMark::NONE_TYPE,
        LaneRoadMark::STANDARD,
        LaneRoadMark::STANDARD_COLOR,
        LaneRoadMark::STANDARD_MATERIAL,
        LaneRoadMark::INCREASE,0.2,0),
    std::make_tuple(100,LaneRoadMark::SOLID,
        LaneRoadMark::BOLD,
        LaneRoadMark::BLUE,
        LaneRoadMark::STANDARD_MATERIAL,
        LaneRoadMark::DECREASE,0.2,-1)));



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}