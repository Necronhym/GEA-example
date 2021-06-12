#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

std::string S= "thequickbrownfoxjumpedoverthelazydog";



class Agent
	{
		std::vector <char> Genome;
		int Fitness;
		char getRandGene(void)
			{
				return 'a' + rand() % 26;
			}
		public:
		Agent(std::string S)
			{
				Fitness = 0;
				for(int i=0; i<S.length(); i++)
					{
						Genome.push_back(getRandGene());
					}
			}
		Agent(std::vector<char> C)
			{
				this->Genome = C;
			}
		void printGenome(void)
			{
				for(auto c: Genome)
					{
						std::cout<< c;
					}
				std::cout<<std::endl;
			}
		void updateFitness(std::string S)
			{
				int f=0;
				for(int i=0; i< Genome.size(); i++)
					{
						if(S.at(i) == Genome.at(i))
							{
								f++;
							}
					}
				this->Fitness = f;
			}
		std::vector<char> getGenome(void)
			{
				return this->Genome;
			}
		int getFitness(void)
			{
				return this->Fitness;
			}
		void setGenome(std::vector<char> newGenome)
			{
				this->Genome = newGenome;
			}
		void mutate()
			{
				Genome.at(rand()%Genome.size()) = getRandGene();
			}
		bool operator< (Agent &Other)
			{
				return Fitness > Other.Fitness;
			}
	};
std::vector<Agent> reproduce(Agent A, Agent B)
	{
		std::vector<bool> Mask;
		std::vector<Agent> Children;
		//generate Mask;
		for(int i=0; i < A.getGenome().size(); i++)
			{
				Mask.push_back(rand() % 2);
			}
		std::vector<char> Child1;
		std::vector<char> Child2;
		int i=0;
		for(auto M: Mask)
			{
				if(M==0)
					{
						Child1.push_back(A.getGenome().at(i));
					}
				else
					{
						Child1.push_back(B.getGenome().at(i));
					}
				i++;
			}
		i=0;
		for(auto M: Mask)
			{
				if(M==1)
					{
						Child2.push_back(A.getGenome().at(i));
					}
				else
					{
						Child2.push_back(B.getGenome().at(i));
					}
				i++;
			}
		Children.push_back(Agent(Child1));
		Children.push_back(Agent(Child2));
		//return
		return Children;
	}

std::vector<Agent> Pop;

int main()
	{
		srand(time(NULL));
		//Create Population of 50:
		for(int i=0; i<100; i++)
			{
				Pop.push_back(Agent(S));
			}
		for(int i=0; i < 250; i ++)
			{
				//Do Check:
				for(auto &A: Pop)
					{
						A.updateFitness(S);
					}
				//Sort pop by fitness
				std::sort(Pop.begin(), Pop.end());
				//Kill lowest performing half of population
				for(int i=0; i<50; i++)
					{
						Pop.pop_back();
					}

				//Reproduction:
				for(int i=49; i>24; i--)
					{
						for( auto A: reproduce(Pop.at(i), Pop.at( 24+ (49-i))))
							{
								Pop.push_back(A);
							}
					}
				for(int i=75; i>25; i--)
					{
						Pop.at(i).mutate();
					}
				if(Pop.at(0).getFitness() == S.length())
					{
						std::cout<<std::endl;
						std::cout<< "Solution reached after " << i << " generations"<<std::endl;
						std::cout<< Pop.at(0).getFitness() << " ";
						Pop.at(0).printGenome();
						break;
					}	
				std::cout<< Pop.at(0).getFitness() << " ";
				Pop.at(0).printGenome();
			}
		return 0;
	}
