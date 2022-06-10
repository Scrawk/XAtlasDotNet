using Microsoft.VisualStudio.TestTools.UnitTesting;

using System;
using System.Collections.Generic;

using XAtlasDotNet.Core;

namespace XAtlasDotNetTest.Core
{
    [TestClass]
    public class ObjLoaderTest
    {
        float[] positions_test = new float[]
        {
                1.000000f, -1.000000f, -1.000000f,
                1.000000f, -1.000000f, 1.000000f,
                -1.000000f, -1.000000f, 1.000000f,
                -1.000000f, -1.000000f, -1.000000f,
                1.000000f, 1.000000f, -0.999999f,
                0.999999f, 1.000000f, 1.000001f,
                -1.000000f, 1.000000f, 1.000000f,
                -1.000000f, 1.000000f, -1.000000f,
        };

        float[] normals_test = new float[]
        {
            0.0000f, -1.0000f, 0.0000f,
            0.0000f, 1.0000f, 0.0000f,
            1.0000f, -0.0000f, 0.0000f,
            0.0000f, -0.0000f, 1.0000f,
            -1.0000f, -0.0000f, -0.0000f,
            0.0000f, 0.0000f, -1.0000f,
        };

        float[] texcoords_test = new float[]
        {
            1.000000f, 0.000000f,
            0.000000f, 1.000000f,
            0.000000f, 0.000000f,
            1.000000f, 0.000000f,
            0.000000f, 1.000000f,
            0.000000f, 0.000000f,
            1.000000f, 0.000000f,
            0.000000f, 1.000000f,
            1.000000f, 0.000000f,
            0.000000f, 1.000000f,
            0.000000f, 0.000000f,
            0.000000f, 0.000000f,
            1.000000f, 1.000000f,
            1.000000f, 0.000000f,
            0.000000f, 1.000000f,
            1.000000f, 1.000000f,
            1.000000f, 1.000000f,
            1.000000f, 1.000000f,
            1.000000f, 0.000000f,
            1.000000f, 1.000000f,
        };

        uint[] indices_test = new uint[]
        {
            2,1,1, 4,2,1, 1,3,1,
            8,4,2, 6,5,2, 5,6,2,
            5,7,3, 2,8,3, 1,3,3,
            6,9,4, 3,10,4, 2,11,4,
            3,12,5, 8,13,5, 4,2,5,
            1,14,6, 8,15,6, 5,6,6,
            2,1,1, 3,16,1, 4,2,1,
            8,4,2, 7,17,2, 6,5,2,
            5,7,3, 6,18,3, 2,8,3,
            6,9,4, 7,17,4, 3,10,4,
            3,12,5, 7,19,5, 8,13,5,
            1,14,6, 4,20,6, 8,15,6,
        };

        Shape shape;

        [TestInitialize]
        public void TestInit()
        {
            string dir = "F:/Projects/Visual Studio Projects/XAtlasDotNet/";
            string filename = dir + "Models/cube.obj";
            ObjLoader.LoadObj(filename);

            ObjLoader.GetShape(0, out shape);
        }

        [TestCleanup]
        public void TestClean()
        {

        }

        [TestMethod]
        public void LoadObj()
        {
            string dir = "F:/Projects/Visual Studio Projects/XAtlasDotNet/";
            string filename = dir + "Models/cube.obj";

            Assert.IsTrue(ObjLoader.LoadObj(filename));
        }

        [TestMethod]
        public void GetIndice()
        {
            int indices = shape.mesh.indices;

            Assert.AreEqual(indices_test.Length / 3, indices);

            for (int i = 0; i < indices; i++)
            {
                //Console.WriteLine(ObjLoader.GetMeshIndice(0, i));
                //Assert.AreEqual(indices_test[i], ObjLoader.GetMeshIndice(0, i));
            }
        }

        [TestMethod]
        public void GetPosition()
        {
            for(int i = 0; i < positions_test.Length; i++)
            {
                //Assert.AreEqual(positions_test[i], ObjLoader.GetMeshPosition(0, i));
            }
        }

        [TestMethod]
        public void GetPositions()
        {

        }

        [TestMethod]
        public void SetPositions()
        {

        }
    }
}