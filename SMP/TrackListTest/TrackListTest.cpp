#include "stdafx.h"
#include "CppUnitTest.h"
#include<iostream>
#include <sstream>
#include<string>
#include<Windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include <boost/filesystem.hpp>
using namespace std;
#pragma comment(lib, "Winmm.lib")

#include "..\..\Source\TrackList.cpp"
#include "..\..\Source\Index.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}


namespace TrackListTest
{		
	TEST_CLASS(TrackListTesting)
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
			TrackList testList("test",testTrack);
			
			Assert::IsTrue(testList.GetTrack(0) == testTrack);
		}

		TEST_METHOD(AddTrack_AddNullTrack_DataEqualsInput)
		{
			Track* testTrack = (Track*)5;
			TrackList testList = TrackList("test");
			testList.AddTrack(testTrack);

			Assert::IsTrue(testList.GetTrack(0) == testTrack);
		}

		TEST_METHOD(AddTrack_AddManyNullTracks_DataEqualsInput)
		{
			Track* testTrack = (Track*)5;
			TrackList testList = TrackList("test");
			testList.AddTrack(testTrack, 0);
			testList.AddTrack(testTrack, 1);
			testList.AddTrack(testTrack, 2);


			Assert::IsTrue(testList.GetTrack(2) == testTrack);
		}

		TEST_METHOD(AddTrack_AddNullTracksWithDifferentValues_DataEqualsInput)
		{
			Track* testTrack = (Track*)5;
			Track* pseudoTestTrack = (Track*)6;
			TrackList testList = TrackList("test");
			testList.AddTrack(pseudoTestTrack);
			testList.AddTrack(pseudoTestTrack);
			testList.AddTrack(pseudoTestTrack);

			testList.AddTrack(testTrack, 1);

			Assert::IsTrue(testList.GetTrack(1) == testTrack);
		}

		TEST_METHOD(GetTrack_AddATonOfTracks_DataIsReturnedQuickly)
		{
			Track* testTrack = (Track*)5;
			TrackList testList = TrackList("test");

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
			TrackList testList = TrackList("test");
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

	TEST_CLASS(TrackTesting)
	{
	public:
		TEST_METHOD(Constructor_NewTrackFromMetadata_MetadataIsStored)
		{
			string metadataArr[5] = { "1","2","3","4","5" };
			Track testTrack = Track(metadataArr);
			
			Assert::AreEqual(testTrack.getMetadata("id"), string("1"));
			Assert::AreEqual(testTrack.getMetadata("title"), string("3"));
		}

		TEST_METHOD(SetMetadata_ChangeMetadata_MetadataIsChanged)
		{
			string metadataArr[METADATA_SIZE] = { "1","2","3","4","5", "6" };
			Track testTrack = Track(metadataArr);

			Assert::AreEqual(testTrack.getMetadata("location"), string("2"));

			testTrack.setMetadata("location", "7");

			Assert::AreEqual(testTrack.getMetadata("location"), string("7"));
		}

		TEST_METHOD(IndexOfThisMetadata_FindIndexOfThisMetadata_MetadataIndexIsCorrect)
		{
			Assert::IsTrue(Track::indexOfThisMetadata("id") == 0);
		}

	};

	TEST_CLASS(MusicPlayerTesting)
	{
	public:
		TEST_METHOD(SlackPostedCode_MakesSound)
		{
			//L"open \" + file path and name + \"....
			string locationOfMusic = "C:\\Users\\Centurion\\Downloads\\Harambe.mp3";
			ostringstream os;
			os << "open \"" << locationOfMusic << "\" type MPEGvideo alias song1";

			string fullInput = os.str();

			LPCSTR a = fullInput.c_str();
			mciSendString(a, NULL, 0, NULL);
			int error2;
			LPCSTR b = "play song1";
			error2 = mciSendString(b, NULL, 0, NULL);
		}
	};

	TEST_CLASS(IndexTesting)
	{
	public:
		TEST_METHOD(IndexConstructor_CanInitiate_NoError)
		{
			Index testIndex;			
		}

		TEST_METHOD(AddDirectory_CanAddDirectory_DirectoryIsSameAsInputAndSizeGoesUp)
		{
			remove(CONFIG_FILE);

			Index testIndex;
			testIndex.AddDirectory("test0");
			testIndex.AddDirectory("test1");
			testIndex.AddDirectory("test2");

			//Assert::AreEqual(string("test1"), testIndex.GetDirectory(1));
			Assert::IsTrue(testIndex.GetDirectorySize() == 3);

		}

		TEST_METHOD(DeleteDirectory_DirectoryIsSameAsThirdInputAndSizeGoesDown)
		{
			remove(CONFIG_FILE);

			Index testIndex;
			testIndex.AddDirectory("test0");
			testIndex.AddDirectory("test1");
			testIndex.AddDirectory("test2");

			testIndex.DeleteDirectory("test1");

			Assert::AreEqual(string("test2"), testIndex.GetDirectory(1));
			Assert::IsTrue(testIndex.GetDirectorySize() == 2);
		}

		TEST_METHOD(WriteFieldsToConfig_CanWriteInitialState_NoError)
		{
			remove(CONFIG_FILE);

			Index testIndex;

			testIndex.AddDirectory("test0");
			testIndex.AddDirectory("test1");
			testIndex.AddDirectory("test2");
		}

		TEST_METHOD(InitiateIndexFromConfig_CanReadInitialState_InititatesAccordingToFile)
		{
			remove(CONFIG_FILE);

			if (true)
			{
				Index testIndex;

				testIndex.AddDirectory("test0");
				testIndex.AddDirectory("test1");
				testIndex.AddDirectory("test2");
			}

			Index testIndex;

			Assert::AreEqual(string("test1"), testIndex.GetDirectory(1));
			Assert::IsTrue(testIndex.GetDirectorySize() == 3);

		}

		TEST_METHOD(WriteTrackList_CanWriteToTextFile_NoError)
		{
			remove(CONFIG_FILE);

			Index testIndex;

			vector<TrackList> in;
			in.push_back(TrackList("test0"));
			in.push_back(TrackList("test1"));
			in.push_back(TrackList("test2"));

			testIndex.WriteTrackListIndex(in);
		}

		TEST_METHOD(ReadTrackList_CanReadFromTextFile_IsCorrect)
		{
			remove(CONFIG_FILE);

			Index testIndex;

			vector<TrackList> in;
			in.push_back(TrackList("test0"));
			in.push_back(TrackList("test1"));
			in.push_back(TrackList("test2"));

			testIndex.WriteTrackListIndex(in);

			vector<TrackList> out = testIndex.ReadTrackListIndex();

			Assert::AreEqual(in[1].name, out[1].name);

		};

		TEST_METHOD(ReadDirectoryContents_CanReadFromGivenDirectories_AnyOutput)
		{
			Index testIndex;

			testIndex.AddDirectory("C:\\Users\\Centurion\\Desktop\\test");

			vector<string> mp3 = testIndex.GetAllEntries();

			Assert::IsTrue(mp3.size() == 1);
		};
	};
}