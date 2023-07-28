#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/*为了找到自己满意的工作， 牛牛收集了每种工作的难度和报酬。 牛牛选工作的标准是在难度不超过自身能力
 *值的情况下， 牛牛选择报酬最高的工作。 在牛牛选定了自己的工作后， 牛牛的小伙伴们来找牛牛帮忙选工作，
 *牛牛依然使用自己的标准来帮助小伙伴们。 牛牛的小伙伴太多了， 于是他只好把这个任务交给了你。
 *
 * class Job {
 *   public int money;// 该工作的报酬
 *   public int hard; // 该工作的难度
 *   public Job(int money, int hard) {
 *       this.money = money;
 *       this.hard = hard;
 *   }
 * }
 *
 * 给定一个Job类型的数组jobarr， 表示所有的工作。
 * 给定一个int类型的数组arr， 表示所有小伙伴的能力。
 * 返回int类型的数组， 表示每一个小伙伴按照牛牛的标准选工作后所能获得的报酬。
 */

struct Job{

    int money;//工作的报酬
    int hard; //工作的难度

    Job(int money, int hard){

        this->money = money;
        this->hard = hard;
    }
};

struct JobComparator{

    bool operator () (Job* job1, Job* job2){

        return job1->hard != job2->hard ? (job1->hard < job2->hard) : (job1->money > job2->money);
    }
};

class ChooseWork{

public:
    vector<int> getMoneys(vector<Job*>& job, vector<int>& ability){

        sort(job.begin(), job.end(), JobComparator());

        map<int, int> jobMap;
        jobMap.insert(make_pair(job[0]->hard, job[0]->money));
        Job* pre = job[0];

        for(int i = 1; i < job.size(); ++i){
            //不在同一组，并且难度系数高报酬高的，留下来
            if(job[i]->hard != pre->hard && job[i]->money > pre->money){

                pre = job[i];
                jobMap.insert(make_pair(job[i]->hard, job[i]->money));
            }
        }

        vector<int> res(ability.size(), 0);
        for(int i = 0; i < ability.size(); ++i){

            map<int, int>::iterator iter = jobMap.begin();
            if(iter->first <= ability[i]){

                int maxs = -1;
                while(iter->first <= ability[i] && iter != jobMap.end()){

                    maxs = iter->second;//报酬
                    ++iter;
                }

                res[i] = maxs;

            }else{

                res[i] = 0;
            }
        }

        return res;
    }
};

int main(int argc, char *argv[])
{
    vector<Job*> jobArr(5, nullptr);

    jobArr[0] = new Job(4, 3);
    jobArr[1] = new Job(5, 2);
    jobArr[2] = new Job(7, 4);
    jobArr[3] = new Job(2, 3);
    jobArr[4] = new Job(4, 2);

    vector<int> ability = {3, 1, 5};

    ChooseWork ans;

    vector<int> res = ans.getMoneys(jobArr, ability);

    for(int i = 0; i <res.size(); ++i)
        cout << res[i] << " ";

    return 0;
}
