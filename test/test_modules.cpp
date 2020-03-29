#include <iostream>
#include <gtest/gtest.h>

#include "modules/ForcePlatforms.h"

TEST(ForcePlatForm, NoPlatForm){
    ezc3d::c3d c3d("c3dTestFiles/Vicon.c3d");
    ezc3d::Modules::ForcePlatforms pf(c3d);
    EXPECT_EQ(pf.forcePlatforms().size(), 0);
}

TEST(ForcePlatForm, AMTI){
    ezc3d::c3d c3d("c3dTestFiles/Qualisys.c3d");
    ezc3d::Modules::ForcePlatforms pf(c3d);
    EXPECT_EQ(pf.forcePlatforms().size(), 2);
    EXPECT_THROW(pf.forcePlatform(2), std::out_of_range);

    const std::vector<ezc3d::Vector3d>& forces(pf.forcePlatform(0).forces());
    const std::vector<ezc3d::Vector3d>& moments(pf.forcePlatform(0).moments());
    const std::vector<ezc3d::Vector3d>& cop(pf.forcePlatform(0).CoP());
    const std::vector<ezc3d::Vector3d>& Tz(pf.forcePlatform(0).Tz());

    EXPECT_DOUBLE_EQ(forces[0](0), 0.13992118835449219);
    EXPECT_DOUBLE_EQ(forces[0](1), 0.046148300170898438);
    EXPECT_DOUBLE_EQ(forces[0](2), -0.18352508544921872);

    EXPECT_DOUBLE_EQ(moments[0](0), 20.867615272954936);
    EXPECT_DOUBLE_EQ(moments[0](1), -4.622511359985765);
    EXPECT_DOUBLE_EQ(moments[0](2), -29.393223381101276);

    EXPECT_DOUBLE_EQ(cop[0](0), 228.81266090518048);
    EXPECT_DOUBLE_EQ(cop[0](1), 118.29556977523387);
    EXPECT_DOUBLE_EQ(cop[0](2), 0.0);

    EXPECT_DOUBLE_EQ(Tz[0](0), 0.0);
    EXPECT_DOUBLE_EQ(Tz[0](1), 0.0);
    EXPECT_DOUBLE_EQ(Tz[0](2), -44.140528790099872);

    // CAL_MATRIX
    for (size_t i=0; i<2; ++i){
        const auto& calMatrix(pf.forcePlatform(i).calMatrix());
        EXPECT_EQ(calMatrix.nbRows(), 6);
        EXPECT_EQ(calMatrix.nbCols(), 6);
        for (size_t j=0; j<6; ++j){
            for (size_t k=0; k<6; ++k){
                EXPECT_EQ(calMatrix(j, k), 0.0);
            }
        }
    }

    // CORNERS
    const auto& corners(pf.forcePlatform(1).corners());
    EXPECT_EQ(corners.size(), 4);
    EXPECT_FLOAT_EQ(corners[0].x(), 1017.0);
    EXPECT_FLOAT_EQ(corners[0].y(), 464.0);
    EXPECT_FLOAT_EQ(corners[0].z(), 0.0);

    EXPECT_FLOAT_EQ(corners[1].x(), 1017.0);
    EXPECT_FLOAT_EQ(corners[1].y(), 0.0);
    EXPECT_FLOAT_EQ(corners[1].z(), 0.0);

    EXPECT_FLOAT_EQ(corners[2].x(), 509.0);
    EXPECT_FLOAT_EQ(corners[2].y(), 0.0);
    EXPECT_FLOAT_EQ(corners[2].z(), 0.0);

    EXPECT_FLOAT_EQ(corners[3].x(), 509.0);
    EXPECT_FLOAT_EQ(corners[3].y(), 464.0);
    EXPECT_FLOAT_EQ(corners[3].z(), 0.0);

    const auto& origin(pf.forcePlatform(1).origin());
    EXPECT_FLOAT_EQ(origin.x(), 1.016);
    EXPECT_FLOAT_EQ(origin.y(), 0);
    EXPECT_FLOAT_EQ(origin.z(),  -36.322);
}
