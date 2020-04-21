//#ifndef VERTEX_TEST_H
//#define VERTEX_TEST_H

//#include <gtest/gtest.h>

//#include <FD3D/Utils/Vertex.h>

//TEST(Vertex_test, constructorTest)
//{
//    float f[9] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 9.0f };
//    FD3D::Vertex v;
//    ASSERT_FLOAT_EQ(v[0], 0.0f);
//    ASSERT_FLOAT_EQ(v[1], 0.0f);
//    ASSERT_FLOAT_EQ(v[2], 0.0f);
//    ASSERT_FLOAT_EQ(v[3], 0.0f);
//    ASSERT_FLOAT_EQ(v[4], 0.0f);
//    ASSERT_FLOAT_EQ(v[5], 0.0f);
//    ASSERT_FLOAT_EQ(v[6], 0.0f);
//    ASSERT_FLOAT_EQ(v[7], 0.0f);

//    v = FD3D::Vertex(2.0f);
//    ASSERT_FLOAT_EQ(v[0], 2.0f);
//    ASSERT_FLOAT_EQ(v[1], 2.0f);
//    ASSERT_FLOAT_EQ(v[2], 2.0f);
//    ASSERT_FLOAT_EQ(v[3], 2.0f);
//    ASSERT_FLOAT_EQ(v[4], 2.0f);
//    ASSERT_FLOAT_EQ(v[5], 2.0f);
//    ASSERT_FLOAT_EQ(v[6], 2.0f);
//    ASSERT_FLOAT_EQ(v[7], 2.0f);

//    v = FD3D::Vertex(f, 9);
//    ASSERT_FLOAT_EQ(v[0], 1.0f);
//    ASSERT_FLOAT_EQ(v[1], 1.0f);
//    ASSERT_FLOAT_EQ(v[2], 1.0f);
//    ASSERT_FLOAT_EQ(v[3], 1.0f);
//    ASSERT_FLOAT_EQ(v[4], 1.0f);
//    ASSERT_FLOAT_EQ(v[5], 1.0f);
//    ASSERT_FLOAT_EQ(v[6], 1.0f);
//    ASSERT_FLOAT_EQ(v[7], 1.0f);


//    FD3D::VertexWrapper w(f);
//    ASSERT_FLOAT_EQ(w[0], 1.0f);
//    ASSERT_FLOAT_EQ(w[1], 1.0f);
//    ASSERT_FLOAT_EQ(w[2], 1.0f);
//    ASSERT_FLOAT_EQ(w[3], 1.0f);
//    ASSERT_FLOAT_EQ(w[4], 1.0f);
//    ASSERT_FLOAT_EQ(w[5], 1.0f);
//    ASSERT_FLOAT_EQ(w[6], 1.0f);
//    ASSERT_FLOAT_EQ(w[7], 1.0f);

//    w = FD3D::VertexWrapper(f, 2.0f);
//    ASSERT_FLOAT_EQ(w[0], 2.0f);
//    ASSERT_FLOAT_EQ(w[1], 2.0f);
//    ASSERT_FLOAT_EQ(w[2], 2.0f);
//    ASSERT_FLOAT_EQ(w[3], 2.0f);
//    ASSERT_FLOAT_EQ(w[4], 2.0f);
//    ASSERT_FLOAT_EQ(w[5], 2.0f);
//    ASSERT_FLOAT_EQ(w[6], 2.0f);
//    ASSERT_FLOAT_EQ(w[7], 2.0f);

//    ASSERT_FLOAT_EQ(f[0], 2.0f);
//    ASSERT_FLOAT_EQ(f[1], 2.0f);
//    ASSERT_FLOAT_EQ(f[2], 2.0f);
//    ASSERT_FLOAT_EQ(f[3], 2.0f);
//    ASSERT_FLOAT_EQ(f[4], 2.0f);
//    ASSERT_FLOAT_EQ(f[5], 2.0f);
//    ASSERT_FLOAT_EQ(f[6], 2.0f);
//    ASSERT_FLOAT_EQ(f[7], 2.0f);

//    float g[6] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
//    w = FD3D::VertexWrapper(f, g, 6);
//    ASSERT_FLOAT_EQ(w[0], 1.0f);
//    ASSERT_FLOAT_EQ(w[1], 1.0f);
//    ASSERT_FLOAT_EQ(w[2], 1.0f);
//    ASSERT_FLOAT_EQ(w[3], 1.0f);
//    ASSERT_FLOAT_EQ(w[4], 1.0f);
//    ASSERT_FLOAT_EQ(w[5], 1.0f);
//    ASSERT_FLOAT_EQ(w[6], 2.0f);
//    ASSERT_FLOAT_EQ(w[7], 2.0f);

//    ASSERT_DEATH(FD3D::VertexWrapper(nullptr), "");
//}

//TEST(Vertex_test, bracketTest)
//{
//    float f[9] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
//    FD3D::Vertex v;
//    FD3D::VertexWrapper w(f);

//    ASSERT_DEATH(v[8], "");
//    ASSERT_DEATH(v[-1], "");
//    ASSERT_DEATH(w[8], "");
//    ASSERT_DEATH(w[-1], "");
//}

//TEST(Vertex_test, componentsTest)
//{
//    float f[8] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };
//    FD3D::Vertex v(f, 8);

//    {
//        glm::vec3 &pos = v.getPosition();
//        ASSERT_FLOAT_EQ(pos.x, 0.0f);
//        ASSERT_FLOAT_EQ(pos.y, 1.0f);
//        ASSERT_FLOAT_EQ(pos.z, 2.0f);

//        pos.x = -1.0f;
//        ASSERT_FLOAT_EQ(v[0], -1.0f);

//        glm::vec3 other(0.0f, 0.0f, 0.0f);
//        v.setPosition(other);
//        ASSERT_FLOAT_EQ(pos.x, 0.0f);
//        ASSERT_FLOAT_EQ(pos.y, 0.0f);
//        ASSERT_FLOAT_EQ(pos.z, 0.0f);
//    }

//    {
//        glm::vec3 &norm = v.getNormal();
//        ASSERT_FLOAT_EQ(norm.x, 3.0f);
//        ASSERT_FLOAT_EQ(norm.y, 4.0f);
//        ASSERT_FLOAT_EQ(norm.z, 5.0f);

//        norm.x = -1.0f;
//        ASSERT_FLOAT_EQ(v[3], -1.0f);

//        glm::vec3 other(0.0f, 0.0f, 0.0f);
//        v.setNormal(other);
//        ASSERT_FLOAT_EQ(norm.x, 0.0f);
//        ASSERT_FLOAT_EQ(norm.y, 0.0f);
//        ASSERT_FLOAT_EQ(norm.z, 0.0f);
//    }

//    {
//        glm::vec2 &tex = v.getTextureCoordinates(0);
//        ASSERT_FLOAT_EQ(tex.x, 6.0f);
//        ASSERT_FLOAT_EQ(tex.y, 7.0f);

//        tex.x = -1.0f;
//        ASSERT_FLOAT_EQ(v[6], -1.0f);

//        glm::vec2 other(0.0f, 0.0f);
//        v.setTexture(other, 0);
//        ASSERT_FLOAT_EQ(tex.x, 0.0f);
//        ASSERT_FLOAT_EQ(tex.y, 0.0f);
//    }

//    FD3D::VertexColorHelper<FD3D::BaseVertex<4>, 0> u(f, 4);
//    {
//        glm::vec4 &col = u.getColor();
//        ASSERT_FLOAT_EQ(col.x, 0.0f);
//        ASSERT_FLOAT_EQ(col.y, 1.0f);
//        ASSERT_FLOAT_EQ(col.z, 2.0f);

//        col.x = -1.0f;
//        ASSERT_FLOAT_EQ(u[0], -1.0f);

//        glm::vec4 other(0.0f, 0.0f, 0.0f, 0.0f);
//        u.setColor(other);
//        ASSERT_FLOAT_EQ(col.x, 0.0f);
//        ASSERT_FLOAT_EQ(col.y, 0.0f);
//        ASSERT_FLOAT_EQ(col.z, 0.0f);
//    }
//}

//#endif // VERTEX_TEST_H
