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
string Int_to_String(int n);  //int转string
void difference(vector<Coin> subSequence1, vector<Coin> subSequence2, vector<Coin> subSequence3, vector<Coin> subSequence4, vector<Coin> &next);
int compareValue(int a, int b);
int main()
{
	system("color 60");
	int CoinsNum, falseCoinWeight, fcoinIndex;  //所有硬币数量，和假币的值 -1 表示轻，1 表示重 和假币的索引
	cout << "!----                   -------!" << endl << endl;
	cout << "!----    请输入总的硬币数量                         -------!" << endl << endl;
	cout << "硬币总数为：";
	cin >> CoinsNum;
	cout << "!----请输入假币的初始位置和假币是重还是轻           -------!" << endl << endl;
	cout << "!----  -1 表示比正常硬币轻，0表示正常，+1表示比正常硬币重--!" << endl << endl;
	cout << "假币的位置："; cin >> fcoinIndex;
	cout << "假币轻重：";   cin >> falseCoinWeight; 
	cout << endl << endl;
	//初始化
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
	cout << "称重次数为" << COMPARETIME << endl << endl;
	cout << "假币的信息" << endl << endl;
	cout << "假币编号：" << falseCoin.initialIndex << endl << endl;
	cout << "假币重量" << falseCoin.coinWeight << endl << endl;
	cout << "称重次数：" << COMPARETIME << endl << endl;
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
			subSequence1[i].currentIndex = i;    //更新子序列的索引
			subSequence2[i].currentIndex = i;
			subSequence3[i].currentIndex = i;
		}
		//余数队列进行更新
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
		return findFalseCoin(nextSequence);  //进行递归   堆栈溢出了。
		//下面进行比较
	}
}
void finalJudge(vector<Coin>sequence, Coin &falseCoin)
{//当错误序列中硬币的数量少于三个则进行最后判断
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
		cout << "最终选取用于比较的硬币编号为：" << index << endl << endl;
		//cout << "第" << index << "个硬币和第" << sequence[0].initialIndex << "的比较结果如图片所示" << endl << endl;
		string a1 = Int_to_String(index);
		for (int i = 0; i < 2; i++)
		{
			string a2 = Int_to_String(sequence[i].initialIndex);
			//string a3 = Int_to_String(sequence[1].initialIndex);
			string answer1 = "第" + a1 + "个硬币和第" + a2 + "的比较结果如图片所示";
			string cmpTime = Int_to_String(COMPARETIME + 1);
			string puttext = "第" + cmpTime + "比较结果";
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
	stream << n;  //n为int类型
	return stream.str();
}

//此函数用于寻找子序列中含有假硬币的子序列
void difference(vector<Coin> subSequence1, vector<Coin> subSequence2, vector<Coin> subSequence3, vector<Coin> subSequence4, vector<Coin> &next)
{
	int sumWeight1 = 0, sumWeight2 = 0, sumWeight3 = 0;  //计算每个子序列的总重量。
	for (int i = 0; i < subSequence1.size(); i++)
	{   
		sumWeight1 = sumWeight1 + subSequence1[i].coinWeight;
		sumWeight2 = sumWeight2 + subSequence2[i].coinWeight;
		sumWeight3 = sumWeight3 + subSequence3[i].coinWeight;
	}
	//进行比较操作
	string cmpTime = Int_to_String(COMPARETIME + 1);
	string puttext = "第" + cmpTime + "次比较结果";
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