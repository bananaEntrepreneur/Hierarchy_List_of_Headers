#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(findParentForParagraph_tests)
	{
	public:
		
		TEST_METHOD(cuurentLevelBiggerThanPrevious)
		{
			Paragraph root = Paragraph("root", nullptr, 0);
			Paragraph A = Paragraph("A", &root, 1);
			root.appendChild(&A);
			Paragraph B = Paragraph("B", &A, 2);
			A.appendChild(&B);

			Paragraph* foundParent = findParentForParagraph(&B, 3);

			Assert::AreEqual(foundParent, &B);
		}

		TEST_METHOD(cuurentLevelEqualPrevious)
		{
			Paragraph root = Paragraph("root", nullptr, 0);
			Paragraph A = Paragraph("A", &root, 1);
			root.appendChild(&A);
			Paragraph B = Paragraph("B", &A, 2);
			A.appendChild(&B);

			Paragraph* foundParent = findParentForParagraph(&B, 2);

			Assert::AreEqual(foundParent, &A);
		}

		TEST_METHOD(cuurentLevelLessThenPrevious)
		{
			Paragraph root = Paragraph("root", nullptr, 0);
			Paragraph A = Paragraph("A", &root, 1);
			root.appendChild(&A);
			Paragraph B = Paragraph("B", &A, 2);
			A.appendChild(&B);
			Paragraph C = Paragraph("C", &A, 2);
			A.appendChild(&C);
			Paragraph D = Paragraph("D", &C, 3);
			C.appendChild(&D);

			Paragraph* foundParent = findParentForParagraph(&D, 1);

			Assert::AreEqual(foundParent, &root);
		}
	};
}
