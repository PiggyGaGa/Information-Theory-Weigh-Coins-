#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
struct Coin
{
	int initialIndex;
	int currentIndex;
	int coinWeight;
};

int COMPARETIME = 0;
Coin findFalseCoin(vector<Coin> haha);
void finalJudge(vector<Coin>sequence, Coin &falseCoin);
string Int_to_String(int n);  //intתstring
void difference(vector<Coin> subSequence1, vector<Coin> subSequence2, vector<Coin> subSequence3, vector<Coin> subSequence4, vector<Coin> &next);
int compareValue(int a, int b);
int main()
{
	system("color 60");
	int CoinsNum, falseCoinWeight, fcoinIndex;  //����Ӳ���������ͼٱҵ�ֵ -1 ��ʾ�ᣬ1 ��ʾ�� �ͼٱҵ�����
	cout << "!----                   -------!" << endl << endl;
	cout << "!----    �������ܵ�Ӳ������                         -------!" << endl << endl;
	cout << "Ӳ������Ϊ��";
	cin >> CoinsNum;
	cout << "!----������ٱҵĳ�ʼλ�úͼٱ����ػ�����           -------!" << endl << endl;
	cout << "!----  -1 ��ʾ������Ӳ���ᣬ0��ʾ������+1��ʾ������Ӳ����--!" << endl << endl;
	cout << "�ٱҵ�λ�ã�"; cin >> fcoinIndex;
	cout << "�ٱ����أ�";   cin >> falseCoinWeight; 
	cout << endl << endl;
	//��ʼ��
	vector<Coin> coinSequence;
	for (int i = 0; i < CoinsNum; i++)
	{
		Coin singleCoin;
		singleCoin.initialIndex = i;
		singleCoin.currentIndex = 0;
		if (i == fcoinIndex - 1)
		{
			singleCoin.coinWeight = falseCoinWeight;
		}
		else
		{
			singleCoin.coinWeight = 0;
		}
		coinSequence.push_back(singleCoin);
		
	}
	Coin falseCoin;
	falseCoin = findFalseCoin(coinSequence);
	cout << "���ش���Ϊ" << COMPARETIME << endl << endl;
	cout << "�ٱҵ���Ϣ" << endl << endl;
	cout << "�ٱұ�ţ�" << falseCoin.initialIndex << endl << endl;
	cout << "�ٱ�����" << falseCoin.coinWeight << endl << endl;
	cout << "���ش�����" << COMPARETIME << endl << endl;
	getchar();
	getchar();
	return 0;
}


Coin findFalseCoin(vector<Coin> sequence)
{
	if (sequence.size() < 3)
	{
		Coin falseCoin;
		finalJudge(sequence, falseCoin);
		return falseCoin;
	}
	else
	{
		int currentSequenceLength = sequence.size();
		vector<Coin> subSequence1, subSequence2, subSequence3, subSequence4;
		for (int i = 0; i < currentSequenceLength / 3; i++)
		{
			subSequence1.push_back(sequence[i]);
			subSequence2.push_back(sequence[i + (currentSequenceLength / 3)]);
			subSequence3.push_back(sequence[i + (currentSequenceLength / 3 * 2)]);
			subSequence1[i].currentIndex = i;    //���������е�����
			subSequence2[i].currentIndex = i;
			subSequence3[i].currentIndex = i;
		}
		//�������н��и���
		for (int i = 0; i < currentSequenceLength % 3; i++)
		{
			if (currentSequenceLength % 3 == 0)
			{
				break;
			}
			subSequence4.push_back(sequence[currentSequenceLength / 3 * 3 + i]);
			subSequence4[i].currentIndex = i;
		}

		vector<Coin> nextSequence;
		difference(subSequence1, subSequence2, subSequence3, subSequence4, nextSequence);
		//Coin falseCoin;
		return findFalseCoin(nextSequence);  //���еݹ�   ��ջ����ˡ�
		//������бȽ�
	}
}
void finalJudge(vector<Coin>sequence, Coin &falseCoin)
{//������������Ӳ�ҵ����������������������ж�
	int length;
	length = sequence.size();
	if (length == 1)
	{
		falseCoin = sequence[0];
	}
	else
	{
		int index = 0;
		while (1)
		{
			if ((sequence[0].initialIndex != index) && (sequence[1].initialIndex != index))
			{
				break;
			}
			else
			{
				index++;
			}
		}
		cout << "����ѡȡ���ڱȽϵ�Ӳ�ұ��Ϊ��" << index << endl << endl;
		//cout << "��" << index << "��Ӳ�Һ͵�" << sequence[0].initialIndex << "�ıȽϽ����ͼƬ��ʾ" << endl << endl;
		string a1 = Int_to_String(index);
		for (int i = 0; i < 2; i++)
		{
			string a2 = Int_to_String(sequence[i].initialIndex);
			//string a3 = Int_to_String(sequence[1].initialIndex);
			string answer1 = "��" + a1 + "��Ӳ�Һ͵�" + a2 + "�ıȽϽ����ͼƬ��ʾ";
			string cmpTime = Int_to_String(COMPARETIME + 1);
			string puttext = "��" + cmpTime + "�ȽϽ��";
			cout << answer1 << endl << endl;
			if (sequence[i].coinWeight < 0)
			{
				cv::Mat blance;
				blance = cv::imread("..//blance//right.jpg");
				//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
				COMPARETIME++;
				cv::namedWindow(answer1);
				cv::imshow(answer1, blance);
				cv::waitKey(1000);
				cv::destroyWindow(answer1);
				falseCoin = sequence[i];
			}
			else if (sequence[i].coinWeight == 0)
			{
				cv::Mat blance;
				blance = cv::imread("..//blance//blance.jpg");
				//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
				COMPARETIME++;
				cv::namedWindow(answer1);
				cv::imshow(answer1, blance);
				cv::waitKey(1000);
				cv::destroyWindow(answer1);
			}
			else
			{
				cv::Mat blance;
				blance = cv::imread("..//blance//left.jpg");
				//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
				COMPARETIME++;
				cv::namedWindow(answer1);
				cv::imshow(answer1, blance);
				cv::waitKey(1000);
				cv::destroyWindow(answer1);
				falseCoin = sequence[i];
			}
		}
		
		
	}
}

string Int_to_String(int n)
{
	ostringstream stream;
	stream << n;  //nΪint����
	return stream.str();
}

//�˺�������Ѱ���������к��м�Ӳ�ҵ�������
void difference(vector<Coin> subSequence1, vector<Coin> subSequence2, vector<Coin> subSequence3, vector<Coin> subSequence4, vector<Coin> &next)
{
	int sumWeight1 = 0, sumWeight2 = 0, sumWeight3 = 0;  //����ÿ�������е���������
	for (int i = 0; i < subSequence1.size(); i++)
	{   
		sumWeight1 = sumWeight1 + subSequence1[i].coinWeight;
		sumWeight2 = sumWeight2 + subSequence2[i].coinWeight;
		sumWeight3 = sumWeight3 + subSequence3[i].coinWeight;
	}
	//���бȽϲ���
	string cmpTime = Int_to_String(COMPARETIME + 1);
	string puttext = "��" + cmpTime + "�αȽϽ��";
	if (compareValue(sumWeight1, sumWeight2) == 0 && compareValue(sumWeight2, sumWeight3) == 0)
	{
		cv::Mat blance;
		blance = cv::imread("..//blance//blance.jpg");
		//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
		COMPARETIME = COMPARETIME + 2;
		cv::namedWindow(puttext);
		cv::imshow(puttext, blance);
		cv::waitKey(1000);
		cv::destroyWindow(puttext);
		next = subSequence4;
	}
	if (compareValue(sumWeight1, sumWeight2) == 1 && compareValue(sumWeight1, sumWeight3) == 1)
	{
		cv::Mat blance;
		blance = cv::imread("..//blance//left.jpg");
		//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
		COMPARETIME = COMPARETIME + 2;
		cv::namedWindow(puttext);
		cv::imshow(puttext, blance);
		cv::waitKey(1000);
		cv::destroyWindow(puttext);
		next = subSequence1;
	}
	if (compareValue(sumWeight1, sumWeight2) == -1 && compareValue(sumWeight1, sumWeight3) == -1)
	{
		cv::Mat blance;
		blance = cv::imread("..//blance//right.jpg");
		//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
		COMPARETIME = COMPARETIME + 2;
		cv::namedWindow(puttext);
		cv::imshow(puttext, blance);
		cv::waitKey(1000);
		cv::destroyWindow(puttext);
		next = subSequence1;
	}

	if (compareValue(sumWeight2, sumWeight1) == 1 && compareValue(sumWeight2, sumWeight3) == 1)
	{
		cv::Mat blance;
		blance = cv::imread("..//blance//left.jpg");
		//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
		COMPARETIME = COMPARETIME + 2;
		cv::namedWindow(puttext);
		cv::imshow(puttext, blance);
		cv::waitKey(1000);
		cv::destroyWindow(puttext);
		next = subSequence2;
	}
	if (compareValue(sumWeight2, sumWeight1) == -1 && compareValue(sumWeight2, sumWeight3) == -1)
	{
		cv::Mat blance;
		blance = cv::imread("..//blance//right.jpg");
		//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
		COMPARETIME = COMPARETIME + 2;
		cv::namedWindow(puttext);
		cv::imshow(puttext, blance);
		cv::waitKey(1000);
		cv::destroyWindow(puttext);
		next = subSequence2;
	}
	if (compareValue(sumWeight3, sumWeight1) == 1 && compareValue(sumWeight3, sumWeight2) == 1)
	{
		cv::Mat blance;
		blance = cv::imread("..//blance//left.jpg");
		//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
		COMPARETIME = COMPARETIME + 2;
		cv::namedWindow(puttext);
		cv::imshow(puttext, blance);
		cv::waitKey(1000);
		cv::destroyWindow(puttext);
		next = subSequence3;
	}

	if (compareValue(sumWeight3, sumWeight1) == -1 && compareValue(sumWeight3, sumWeight2) == -1)
	{
		cv::Mat blance;
		blance = cv::imread("..//blance//left.jpg");
		//cv::putText(blance, puttext, cv::Point(blance.rows / 2, blance.cols / 4), CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0));
		COMPARETIME = COMPARETIME + 2;
		cv::namedWindow(puttext);
		cv::imshow(puttext, blance);
		cv::waitKey(1000);
		cv::destroyWindow(puttext);
		next = subSequence3;
	}

}
int compareValue(int a, int b)
{
	if (a > b)
	{
		return 1;
	}
	else if (a == b)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}