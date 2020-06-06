//#ifndef CAMERA_TEST_H
//#define CAMERA_TEST_H

//#include <gtest/gtest.h>

//#include <FD3D/Camera/Camera.h>

//TEST(Camera_test, setPostionTest)
//{
//    glm::vec3 v(1.0f, 2.0f, 3.0f);
//    FD3D::Camera cam;
//    cam.setPosition(v);
//    ASSERT_EQ(v, cam.getPosition());
//}

//TEST(Camera_test, translateTest)
//{
//    glm::vec3 v(1.0f, 2.0f, 3.0f);
//    FD3D::Camera cam;
//    cam.setPosition(v);
//    cam.translate(v);
//    ASSERT_EQ(v * 2.0f, cam.getPosition());
//}

//TEST(Camera_test, setRotationTest)
//{
//    glm::vec3 r(glm::radians(1.0f), glm::radians(2.0f), glm::radians(3.0f));
//    FD3D::Camera cam;
//    cam.setRotation(r);
//    glm::vec3 result = cam.getEulerAngles();
//    EXPECT_FLOAT_EQ(1.0f, result.x);
//    EXPECT_FLOAT_EQ(2.0f, result.y);
//    EXPECT_FLOAT_EQ(3.0f, result.z);

//    r = glm::vec3(glm::radians(5.0f), glm::radians(5.0f), glm::radians(5.0f));
//    glm::quat q = glm::quat(r);

//    cam.setRotation(r);
//    EXPECT_EQ(q, cam.getRotation());
//    result = cam.getEulerAngles();
//    EXPECT_FLOAT_EQ(5.0f, result.x);
//    EXPECT_FLOAT_EQ(5.0f, result.y);
//    EXPECT_FLOAT_EQ(5.0f, result.z);
//}

//TEST(Camera_test, rotateTest)
//{
//    glm::vec3 r(glm::radians(90.0f), 0.0f, glm::radians(0.0f));
//    FD3D::Camera cam;
//    cam.setRotation(glm::vec3{0.0f});
//    cam.rotate(r);
//    glm::vec3 result = cam.getEulerAngles();
//    EXPECT_NEAR(90.0f, result.x, 3.0f);
//    EXPECT_NEAR(0.0f, result.y, 3.0f);
//    EXPECT_NEAR(0.0f, result.z, 3.0f);

//    r = glm::vec3(glm::radians(27.0f), glm::radians(5.0f), glm::radians(18.0f));
//    glm::quat q = glm::quat(r);

//    cam.rotate(q);
//    result = cam.getEulerAngles();
//    EXPECT_NEAR(117.0f, result.x, 3.0f);
//    EXPECT_NEAR(-18.0f, result.y, 3.0f); // y axis is inverted due to base orientation
//    EXPECT_NEAR(5.0f, result.z, 3.0f); // y and z are swapped within euler angles
//}

//TEST(Camera_test, upVectorTest)
//{
//    FD3D::Camera cam;
//}

//#endif // CAMERA_TEST_H
