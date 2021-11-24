#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::string PositionToString(int position)
{
    switch (position)
    {
    case 0:
        return "top row";
    case 1:
        return "middle row";
    case 2:
        return "lower row";
    case 3:
        return "left column";
    case 4:
        return "middle column";
    case 5:
        return "right column";
    case 6:
        return "top left to bottom right";
    case 7:
        return "top right to bottom left";
    default:
        return std::to_string(position);
    }
}

const std::vector<std::tuple<int, int>> c_ValueToPoints{
    {6, 10000},
    {24, 3600},
    {23, 1800},
    {21, 1080},
    {8, 720},
    {9, 360},
    {20, 306},
    {11, 252},
    {15, 180},
    {17, 180},
    {22, 144},
    {18, 119},
    {12, 108},
    {10, 80},
    {13, 72},
    {16, 72},
    {14, 54},
    {7, 36},
    {19, 36}
};

std::vector<int> FillBoard(const std::vector<int>& currentBoard, int numbers[], int size)
{
    auto boardToFillIn{ currentBoard };

    int indexToFillIn{};

    for (int indexOnBoard = 0; indexOnBoard < boardToFillIn.size(); indexOnBoard++)
    {
        if (boardToFillIn[indexOnBoard] == 0)
        {
            boardToFillIn[indexOnBoard] = numbers[indexToFillIn++];
        }
    }

    return boardToFillIn;
}

std::vector<int> CalculateSums(const std::vector<int>& currentBoard)
{
    std::vector<int> sums{ 0, 0, 0, 0, 0, 0, 0, 0 };

    // top row
    sums[0] = currentBoard[0] + currentBoard[1] + currentBoard[2];

    // middle row
    sums[1] = currentBoard[3] + currentBoard[4] + currentBoard[5];

    // bottom row
    sums[2] = currentBoard[6] + currentBoard[7] + currentBoard[8];

    // left column
    sums[3] = currentBoard[0] + currentBoard[3] + currentBoard[6];

    // middle column
    sums[4] = currentBoard[1] + currentBoard[4] + currentBoard[7];

    // right column
    sums[5] = currentBoard[2] + currentBoard[5] + currentBoard[8];

    // top left to bottom right
    sums[6] = currentBoard[0] + currentBoard[4] + currentBoard[8];

    // top right to bottom left
    sums[7] = currentBoard[2] + currentBoard[4] + currentBoard[6];

    return sums;
}

void AddSums(std::map<int, std::vector<int>>& countOfSums, const std::vector<int>& board)
{
    for (int sumLocation = 0; sumLocation < 8; sumLocation++)
    {
        int sumAtPosition{ board[sumLocation] };
        countOfSums[sumLocation][sumAtPosition]++;
    }
}

std::map<int, std::vector<double>> CalculateChance(const std::map<int, std::vector<int>>& countOfSums)
{
    std::map<int, std::vector<double>> sumPositionToPercentages{};

    for (int sumPosition = 0; sumPosition < 8; sumPosition++)
    {
        sumPositionToPercentages.insert(std::pair<int, std::vector<double>>(sumPosition, std::vector<double>(25, 0)));

        auto countOfSum{ countOfSums.at(sumPosition) };

        int countOfAllPossabilities{};
        for (auto&& sum : countOfSum)
        {
            countOfAllPossabilities += sum;
        }

        for (int sumCount = 6; sumCount < 25; sumCount++)
        {
            double sumChance{ static_cast<double>(countOfSum[sumCount]) / static_cast<double>(countOfAllPossabilities) };

            sumPositionToPercentages[sumPosition][sumCount] = sumChance;
        }
    }

    return sumPositionToPercentages;
}

std::map<int, std::vector<std::tuple<int, double>>> ConvertPointsToMGP(const std::map<int, std::vector<double>>& positionToPercentage)
{
    // std::map<revealSelectionAsInt, std::vector<std::tuple<MGP, percentage>>>
    std::map<int, std::vector<std::tuple<int, double>>> positionToMGP{};


    for (int position = 0; position < 8; position++)
    {
        positionToMGP.insert({ 1, {} });
        auto positionAndPercentage{ positionToPercentage.at(position) };

        for (int possibleSum = 6; possibleSum < 25; possibleSum++)
        {
            double percentage{ positionAndPercentage [possibleSum]};

            int mgpValue{};

            for (auto&& pointToMgp : c_ValueToPoints)
            {
                if (std::get<0>(pointToMgp) == possibleSum)
                {
                    mgpValue = std::get<1>(pointToMgp);
                    break;
                }
            }

            if (percentage != 0 && mgpValue != 0)
            {
                positionToMGP[position].push_back({mgpValue, percentage});
            }
        }

    }

    return positionToMGP;
}

void PrintTopThreePercentagesForEachPosition(const std::map<int, std::vector<std::tuple<int, double>>>& mgpsToPercentages)
{
    for (int position = 6; position < 25; position++)
    {
        std::cout << "Highest percentage for " << PositionToString(position);
    }
}

int main(int argc, char** argv)
{
    if (argc != 9)
    {
        std::cout << "Need 8 arguments" << std::endl;
        return 0;
    }

    std::vector<int> board{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    std::list<int> numbersRemaining{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::list<int> numbersRevealed{};

    int firstNumberLocation{ std::stoi(argv[1]) };
    int firstNumberValue{ std::stoi(argv[2]) };
    numbersRemaining.remove(firstNumberValue);
    numbersRevealed.push_back(firstNumberValue);

    int secondNumberLocation{ std::stoi(argv[3]) };
    int secondNumberValue{ std::stoi(argv[4]) };
    numbersRemaining.remove(secondNumberValue);
    numbersRevealed.push_back(secondNumberValue);

    int thirdNumberLocation{ std::stoi(argv[5]) };
    int thirdNumberValue{ std::stoi(argv[6]) };
    numbersRemaining.remove(thirdNumberValue);
    numbersRevealed.push_back(thirdNumberValue);

    int freeNumberLocation{ std::stoi(argv[7]) };
    int freeNumberValue{ std::stoi(argv[8]) };
    numbersRemaining.remove(freeNumberValue);
    numbersRevealed.push_back(freeNumberValue);

    board[firstNumberLocation] = firstNumberValue;
    board[secondNumberLocation] = secondNumberValue;
    board[thirdNumberLocation] = thirdNumberValue;
    board[freeNumberLocation] = freeNumberValue;

    std::map<int, std::vector<int>> possibleValues{};

    int permutationArray[5];
    int index{};
    for (auto&& numberRemaining : numbersRemaining)
    {
        permutationArray[index++] = numberRemaining;
    }

    std::map<int, std::vector<int>> sumsToCountOfSums{};

    for (int sumPosition = 0; sumPosition < 8; sumPosition++)
    {
        sumsToCountOfSums.insert(std::pair<int, std::vector<int>>(sumPosition, std::vector<int>(25, 0)));
    }

    auto filledInBoard{ FillBoard(board, permutationArray, 5) };
    auto calculatedSums{ CalculateSums(filledInBoard) };
    AddSums(sumsToCountOfSums, calculatedSums);

    while (std::next_permutation(permutationArray, permutationArray + 5))
    {
        auto filledInBoard{ FillBoard(board, permutationArray, 5) };
        auto calculatedSums{ CalculateSums(filledInBoard) };
        AddSums(sumsToCountOfSums, calculatedSums);
    }

    auto sumPositionToChance{ CalculateChance(sumsToCountOfSums) };
    auto pointsToPercentage{ConvertPointsToMGP(sumPositionToChance)};
    PrintTopThreePercentagesForEachPosition(pointsToPercentage);
}
