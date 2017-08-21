# 问题重述
一般性假币称重鉴别问题：设有n枚硬币，其中仅有一枚假币，在已知或未知假币与真比之间重量关系两种情况下，通过无砝码天平称重的方法鉴别假币，求所需的最少称重次数。
# 题目要求
1. 试用信息论的原理进行分析，并给出n=12,39的具体称重策略；
2. 编程实现可视化。
# 实验原理
**从熵的角度考虑**
根据熵的可加性，一个复合事件的不确定性可以通过多次试验逐步解除。如果每次实验所获的信息量都是可以获得的最大信息量，那么所需要的实验次数就可以最少。基于这个原理考虑这个问题，天平一次称重会有三种结果，且每一种结果的概率都是1/3，那么进行一次称重所获的信息量是 ，k次称重所获得的最大信息量是 。如果一共有n个硬币，且已知有一枚假币(不知道是否轻或重)，那么找到这枚假币所需的信息量是 ，那么想要称重最少只需求如下优化问题
$$min k \\ s.t. klog_23 \geq log_22n \\ k \in N^*, n \geq 3$$
转化为:$$ f(n)=\lceil log_22n/log_23 \rceil, n \geq 3$$
其中n是给定的正整数，显然这个问题是可解的，所以按照信息论理论，最少的称重次数是存在的。
**从编程的角度考虑**
数学研究的是某个问题的解是否存在，编程需要考虑的是如果问题的解存在，如何去解，如果不存在，如何计算可达到的实际中的较优的值。上面从信息论的角度讨论了称硬币实验的最少称重次数是存在的，进一步思考这个问题，既然理论上最少称重次数是存在的，那理论能否能结合实践达到最少称重的目的呢？
	最少的称重次数存在，如何去称重是另一个需要解决的问题。这个问题的核心在于称重方式的设计。计算机比人类优越的点在于运算速度快，但缺点是复杂逻辑的运算较为困难。借助计算机来计算称重过程需要设计好称重规则，遇到不同的情况采取不同的策略。
# 我的算法-三分法
算法思路：给出n个硬币，依次编号为1-n，将n个硬币平局分成三份，均分后会产生一组余数组，余数组是将硬币总数除以3后的余数个数的硬币组。余数组的数目可为0、1、2。每一个均分组作为一个单位，对三个均分组进行称重，最终会找到某一组的质量和其他两组不同，那么有问题的硬币就在这一组。如果三个均分组的质量相同，那么余数组就是有问题的组。同样，对有问题组进行三分，并按照上述步骤进行操作，直到有问题组的硬币数少于3，最后找一个正常的硬币和有问题组的硬币分别进行称量，即可找到有问题的硬币，并判断其是重还是轻。
以n=12为例算法流程如下图所示
![Algorithm](http://or6i73qhr.bkt.clouddn.com/InformationTheory-Algorithm.png "算法流程")
如图所示，共有12个硬币，其中有一个是假币，每次将硬币均分成三堆，和一组余数组，先对均分的三堆进行称重，找出有问题的那一堆，再次进行重复的操作，最终找到有问题的那枚硬币。
# 实验程序设计
1.	编程语言和相关库
编程语言：c++
相关的库：基本输入输出库iostream和用于可视化的库opencv3.2
2.	程序设计
1.	基本结构和重要变量
```
a.	struct Coin
{
	int initialIndex;
	int currentIndex;
	int coinWeight;
}
```
自定义结构Coin用来存储一个硬币的信息
b.	vector<Coin> coinSequence
定义Coin vector向量存储一堆硬币的信息
c.	int COMPARETIME
设置int类型全局变量用来存储称重的次数。
2.	核心函数
a.`	Coin findFalseCoin(vector<Coin> haha)`
此函数输入一堆硬币，返回值是假币对应的结构。此函数用于递归操作，是整个程序的核心函数。
b.	`void finalJudge(vector<Coin>sequence, Coin &falseCoin)`
此函数用作最终的判断，如果一堆的硬币数少于3执行此函数，找到假币返回结果。
c.	`void difference(vector<Coin> subSequence1, vector<Coin> subSequence2, vector<Coin> subSequence3, vector<Coin> subSequence4, vector<Coin> &next)`
此函数用在分堆后，功能是找到哪一堆是含有假币的堆。
d.	`int compareValue(int a, int b)`
此函数用于较，该函数具有天平称重的作用，返回较重的一枚硬币。
3.	程序流程
第一步：初始化。将n枚硬币依次编号，按顺序排列，并给出有问题的硬币的索引，可以指定，也可以随机在1-n之间选取一个数。并标注该硬币比正常硬币重还是轻。
第二步：判断结束条件。如果该堆硬币的个数少于3个，那么执行第四部，否则执行第三步。
第三步：分堆。所有硬币均分成三堆，并称重。三个均分的堆通过称重可以称得哪一堆的质量和另外两堆不同，此步骤返回结果就是这一堆硬币。如果三堆的质量都相同，此步骤返回的结果是余数堆。执行第二步
第四步：如果该堆的硬币数是1，那么该硬币就是有问题的硬币，找一个正常的硬币和它进行称重，可以得到它比正常硬币轻或重。如果该堆硬币的个数是2，找一个正常硬币分别和它们进行称重，同样也可以得到那个假币和它的轻重情况。  
# 实验结果分析

![硬币总数为12](http://or6i73qhr.bkt.clouddn.com/answer10.png "硬币总数为12")

![硬币总数为39](http://or6i73qhr.bkt.clouddn.com/answer20.png "硬币总数为39")
初始给定硬币总数为12，假币的位置这里没有设置随机，程序运行开始我给指定为4，假币轻重的标识为-1，表示假币要比正常硬币轻。最后得到结果是符合的，结果返回的假币编号比假币位置少1是因为编号是从0到(n-1)而位置是从1到n的。最终用4次称重得到结果。给定不同的假币位置最终称重次数会有所不同。当初始硬币数为39，假币位置设为10，假币表示为+1，最终用6次称重得到结果
## 2.	复杂度分析
本程序采用递归方式进行计算，每次递归减少硬币的数量为上一次硬币数量的1/3，所以时间复杂度为 ，平均进行了 次递归操作，每次递归操作要进行两次称重，所以平均称重次数为 。显然这种方法不能使称重次数达到最少，通过n=12时用三次就可以得到结果的方法进行分析，得到的结论是：要想得到最少称重次数，必须考虑多种情况，并进行多种判断，逻辑相对复杂。而三分算法没有设计那种过于复杂的逻辑判断，所以不能实现称重次数最少。
# 完整的实验代码

```
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
	cout << "!----    14070110007           高宇达               -------!" << endl << endl;
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

```


# 问题重述
一般性假币称重鉴别问题：设有n枚硬币，其中仅有一枚假币，在已知或未知假币与真比之间重量关系两种情况下，通过无砝码天平称重的方法鉴别假币，求所需的最少称重次数。
# 题目要求
1. 试用信息论的原理进行分析，并给出n=12,39的具体称重策略；
2. 编程实现可视化。
# 实验原理
**从熵的角度考虑**
根据熵的可加性，一个复合事件的不确定性可以通过多次试验逐步解除。如果每次实验所获的信息量都是可以获得的最大信息量，那么所需要的实验次数就可以最少。基于这个原理考虑这个问题，天平一次称重会有三种结果，且每一种结果的概率都是1/3，那么进行一次称重所获的信息量是 ，k次称重所获得的最大信息量是 。如果一共有n个硬币，且已知有一枚假币(不知道是否轻或重)，那么找到这枚假币所需的信息量是 ，那么想要称重最少只需求如下优化问题
$$min k \\ s.t. klog_23 \geq log_22n \\ k \in N^*, n \geq 3$$
转化为:$$ f(n)=\lceil log_22n/log_23 \rceil, n \geq 3$$
其中n是给定的正整数，显然这个问题是可解的，所以按照信息论理论，最少的称重次数是存在的。
**从编程的角度考虑**
数学研究的是某个问题的解是否存在，编程需要考虑的是如果问题的解存在，如何去解，如果不存在，如何计算可达到的实际中的较优的值。上面从信息论的角度讨论了称硬币实验的最少称重次数是存在的，进一步思考这个问题，既然理论上最少称重次数是存在的，那理论能否能结合实践达到最少称重的目的呢？
	最少的称重次数存在，如何去称重是另一个需要解决的问题。这个问题的核心在于称重方式的设计。计算机比人类优越的点在于运算速度快，但缺点是复杂逻辑的运算较为困难。借助计算机来计算称重过程需要设计好称重规则，遇到不同的情况采取不同的策略。
# 我的算法-三分法
算法思路：给出n个硬币，依次编号为1-n，将n个硬币平局分成三份，均分后会产生一组余数组，余数组是将硬币总数除以3后的余数个数的硬币组。余数组的数目可为0、1、2。每一个均分组作为一个单位，对三个均分组进行称重，最终会找到某一组的质量和其他两组不同，那么有问题的硬币就在这一组。如果三个均分组的质量相同，那么余数组就是有问题的组。同样，对有问题组进行三分，并按照上述步骤进行操作，直到有问题组的硬币数少于3，最后找一个正常的硬币和有问题组的硬币分别进行称量，即可找到有问题的硬币，并判断其是重还是轻。
以n=12为例算法流程如下图所示
![Algorithm](http://or6i73qhr.bkt.clouddn.com/InformationTheory-Algorithm.png "算法流程")
如图所示，共有12个硬币，其中有一个是假币，每次将硬币均分成三堆，和一组余数组，先对均分的三堆进行称重，找出有问题的那一堆，再次进行重复的操作，最终找到有问题的那枚硬币。
# 实验程序设计
1.	编程语言和相关库
编程语言：c++
相关的库：基本输入输出库iostream和用于可视化的库opencv3.2
2.	程序设计
1.	基本结构和重要变量
```
a.	struct Coin
{
	int initialIndex;
	int currentIndex;
	int coinWeight;
}
```
自定义结构Coin用来存储一个硬币的信息
b.	vector<Coin> coinSequence
定义Coin vector向量存储一堆硬币的信息
c.	int COMPARETIME
设置int类型全局变量用来存储称重的次数。
2.	核心函数
a.`	Coin findFalseCoin(vector<Coin> haha)`
此函数输入一堆硬币，返回值是假币对应的结构。此函数用于递归操作，是整个程序的核心函数。
b.	`void finalJudge(vector<Coin>sequence, Coin &falseCoin)`
此函数用作最终的判断，如果一堆的硬币数少于3执行此函数，找到假币返回结果。
c.	`void difference(vector<Coin> subSequence1, vector<Coin> subSequence2, vector<Coin> subSequence3, vector<Coin> subSequence4, vector<Coin> &next)`
此函数用在分堆后，功能是找到哪一堆是含有假币的堆。
d.	`int compareValue(int a, int b)`
此函数用于较，该函数具有天平称重的作用，返回较重的一枚硬币。
3.	程序流程
第一步：初始化。将n枚硬币依次编号，按顺序排列，并给出有问题的硬币的索引，可以指定，也可以随机在1-n之间选取一个数。并标注该硬币比正常硬币重还是轻。
第二步：判断结束条件。如果该堆硬币的个数少于3个，那么执行第四部，否则执行第三步。
第三步：分堆。所有硬币均分成三堆，并称重。三个均分的堆通过称重可以称得哪一堆的质量和另外两堆不同，此步骤返回结果就是这一堆硬币。如果三堆的质量都相同，此步骤返回的结果是余数堆。执行第二步
第四步：如果该堆的硬币数是1，那么该硬币就是有问题的硬币，找一个正常的硬币和它进行称重，可以得到它比正常硬币轻或重。如果该堆硬币的个数是2，找一个正常硬币分别和它们进行称重，同样也可以得到那个假币和它的轻重情况。  
# 实验结果分析

![硬币总数为12](http://or6i73qhr.bkt.clouddn.com/answer10.png "硬币总数为12")

![硬币总数为39](http://or6i73qhr.bkt.clouddn.com/answer20.png "硬币总数为39")
初始给定硬币总数为12，假币的位置这里没有设置随机，程序运行开始我给指定为4，假币轻重的标识为-1，表示假币要比正常硬币轻。最后得到结果是符合的，结果返回的假币编号比假币位置少1是因为编号是从0到(n-1)而位置是从1到n的。最终用4次称重得到结果。给定不同的假币位置最终称重次数会有所不同。当初始硬币数为39，假币位置设为10，假币表示为+1，最终用6次称重得到结果
## 2.	复杂度分析
本程序采用递归方式进行计算，每次递归减少硬币的数量为上一次硬币数量的1/3，所以时间复杂度为 ，平均进行了 次递归操作，每次递归操作要进行两次称重，所以平均称重次数为 。显然这种方法不能使称重次数达到最少，通过n=12时用三次就可以得到结果的方法进行分析，得到的结论是：要想得到最少称重次数，必须考虑多种情况，并进行多种判断，逻辑相对复杂。而三分算法没有设计那种过于复杂的逻辑判断，所以不能实现称重次数最少。
