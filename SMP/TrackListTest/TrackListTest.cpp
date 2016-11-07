#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\..\Source\TrackList.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TrackListTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		//Example naming convention for a test method
		TEST_METHOD(SubjectOfTest_DescriptionOfTest_PredictedOutcomeOfTest)
		{
			// TODO: Your test code here
			Assert::IsTrue(1 == 1);
		}

		TEST_METHOD(Constructor_InstantiateWithNullTrack_DataEqualsInput)
		{
			Track* testTrack = (Track*)5;
			TrackList testList = TrackList(testTrack);
			
			Assert::IsTrue(testList.GetTrack(0) == testTrack);
		}

		TEST_METHOD(AddTrack_AddNullTrack_DataEqualsInput)
		{
			Track* testTrack = (Track*)5;
			TrackList testList = TrackList();
			testList.AddTrack(testTrack);

			Assert::IsTrue(testList.GetTrack(0) == testTrack);
		}

		TEST_METHOD(AddTrack_AddManyNullTracks_DataEqualsInput)
		{
			Track* testTrack = (Track*)5;
			TrackList testList = TrackList();
			testList.AddTrack(testTrack, 0);
			testList.AddTrack(testTrack, 1);
			testList.AddTrack(testTrack, 2);


			Assert::IsTrue(testList.GetTrack(2) == testTrack);
		}

		TEST_METHOD(AddTrack_AddNullTracksWithDifferentValues_DataEqualsInput)
		{
			Track* testTrack = (Track*)5;
			Track* pseudoTestTrack = (Track*)6;
			TrackList testList = TrackList();
			testList.AddTrack(pseudoTestTrack);
			testList.AddTrack(pseudoTestTrack);
			testList.AddTrack(pseudoTestTrack);

			testList.AddTrack(testTrack, 1);

			Assert::IsTrue(testList.GetTrack(1) == testTrack);
		}

		TEST_METHOD(GetTrack_AddATonOfTracks_DataIsReturnedQuickly)
		{
			Track* testTrack = (Track*)5;
			TrackList testList = TrackList();

			for (int i = 0; i < 10000; i++)
			{
				testList.AddTrack(testTrack);
			}

			Assert::IsTrue(testList.GetTrack(9999) == testTrack);
		}

		TEST_METHOD(RemoveTrack_RemoveTrackChangesValueToNextTrack_DataEqualsInput)
		{
			Track* testTrack = (Track*)5;
			Track* pseudoTestTrack = (Track*)6;
			TrackList testList = TrackList();
			testList.AddTrack(pseudoTestTrack);
			testList.AddTrack(pseudoTestTrack);
			testList.AddTrack(testTrack);
			testList.AddTrack(pseudoTestTrack);
			testList.AddTrack(pseudoTestTrack);

			Assert::IsTrue(testList.GetTrack(2) == testTrack);
			testList.RemoveTrack(2);
			Assert::IsTrue(testList.GetTrack(2) == pseudoTestTrack);
		}


	};
}