using NUnit.Framework;
using JsonLib;
using System.IO;
using System;


namespace JsonLabTest
{
    public class Tests
    {
        [SetUp]
        public void Setup()
        {
        }

        [Test]
        public void Test1()
        {
            Json tmp = new Json();
            //tmp

            Console.WriteLine("Hello");
            Assert.Pass();
        }
    }
}