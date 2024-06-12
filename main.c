#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int deck[5][15] = { 0 };
int scoreUser = 0, scoreAi = 0;
//숫자 출력(숫자num)
void num(int randNum) {
	switch (randNum) {
	case 1: printf("A"); break;
	case 11: printf("J"); break;
	case 12: printf("Q"); break;
	case 13: printf("K"); break;
	default: printf("%d", randNum); break;
	}
}
//모양 출력(모양num)
void shape_(int shape) {
	switch (shape) {
	case 0: printf("♠ "); break;
	case 1: printf("♥ "); break;
	case 2: printf("◆ "); break;
	case 3: printf("♣ "); break;
	}
}
//점수 계산(숫자num)
int CardScore(int Number) {
	int score = 0;
	switch (Number) {
	case 1:
		if (score + 11 < 21)
			score += 11;
		else
			score += 1;
		break;
	case 11: score += 10; break;
	case 12: score += 10; break;
	case 13: score += 10; break;
	default: score += Number; break;
	}
	return score;
}
//중복 없이 카드 뽑기(출력X == 0,출력O == 10,User == 1,)
void card(int AorU) {
	while (1)
	{
		int CardNum = rand() % 13 + 1;
		int CardShape = rand() % 4;
		if (deck[CardShape][CardNum] == 0) {
			deck[CardShape][CardNum] = 1;
			if (AorU == 0)
				scoreAi += CardScore(CardNum);
			else if (AorU == 1) {
				scoreUser += CardScore(CardNum);
				shape_(CardShape);
				num(CardNum);
			}
			else if (AorU == 10) {
				scoreAi += CardScore(CardNum);
				shape_(CardShape);
				num(CardNum);
			}
			break;
		}
	}
}

int main() {
	srand(time(NULL));
	printf("\n");  // 보기 불편하니까 한 칸 띄우기

	//카드 출력
	printf("Computer Card : ");
	card(10);
	printf(" ??\n");
	card(0);
	printf("    User Card : ");
	card(1);
	printf(" ");
	card(1);

	printf("\n\n");

	//점수 출력
	//printf("Computer Score : %d\n",scoreAi);
	printf("    User Score : %d\n", scoreUser);

	//블랙잭 판단
	if (scoreUser == 21) {
		printf("\n블랙잭으로 승리했습니다.");
		return 0;
	}
	else if (scoreUser == 21 && scoreAi == 21) {
		printf("\n무승부했습니다.");
		return 0;
	}

	//Ai 카드 더 받기
	while (1) {
		if (scoreAi <= 16) {
			card(0);
		}
		else if (scoreAi >= 17)
			break;
	}

	//카드 더 받기
	char nswer;
	printf("카드를 더 받을까요?\n");
	printf("(Y/N) : ");
	while (1) {
		scanf("%c", &nswer);
		if (nswer == 'Y') {
			card(1);
			printf("    User Score : %d\n", scoreUser);
			if (scoreUser > 21) {
				printf("\n패배했습니다.");
				return 0;
			}
			printf("카드를 더 받을까요?\n");
			printf("(Y/N) : ");
			continue;
		}
		else if (nswer == 'N')
			break;
	}

	//승패
	printf("Computer Score : %d\n", scoreAi);
	printf("    User Score : %d\n", scoreUser);
	if (scoreAi > 21)
		printf("\n승리했습니다");
	else if (21 - scoreAi < 21 - scoreUser)
		printf("\n패배했습니다.");
	else if (21 - scoreAi > 21 - scoreUser || scoreAi > 21)
		printf("\n승리했습니다.");
	else if (scoreAi == scoreUser)
		printf("\n무승부했습니다.");

	return 0;
}

//카드의 합이 21에 가장 가까운 사람이 승리합니다
//플레이어는 처음 받은 카드(2장) 이외에 원하는 만큼 카드를 더 받을 수 있습니다
//카드를 더 받으며 합이 21이 넘는 경우 즉시 패배합니다
//처음 받은 패(2장)의 합이 21일 경우 즉시 해당 사람이 승리합니다
//Ai(딜러)는 무조건 16 이하면 카드를 받고, 17 이상이면 카드를 받지 않습니다
//A는 받은 시점의 점수에서 11을 더했을 때 21을 넘을 경우 1,넘지 않을경우 11로 계산합니다
