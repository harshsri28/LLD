#include<bits/stdc++.h>
using namespace std;


class Posts{
    private:
    int id;
    string content;

    public:
    Posts(int id, string content) : id(id) , content(content) {}

    void setContentPost(){
        content = content;
    }

    string getContent(){
        return content;
    }
};

class Jobs{
    private:
    int jobId;
    string roleDescription;

    public:
    Jobs(int jobId, string roleDescription ) : jobId(jobId), roleDescription(roleDescription) {}

    void setJobId(int jobId){
        jobId = jobId;
    }

    int getJobId(){
        return jobId;
    }

    void setRoleDescription(string newRoleDescription){
        roleDescription = newRoleDescription;
    }

    string getRoleDescription(){
        return roleDescription;
    }
};

class Users{
    private:
    int id;
    string name;
    string description;
    int connections;
    vector<Users*> userConnections;
    vector<Posts> userPosts;
    vector<Jobs> userJobsApplied;
    

    public:
    Users(string name, string description, int id) : name(name) , description(description), id(id){}

    void setName(string newName){
        name = newName;
    }

    string getName(){
        return name;
    }

    vector<Users*> getUserConnectionsList(){
        return userConnections;
    }

    void addConnection(Users* user){
        userConnections.push_back(user);
    }

    vector<Posts> getUserPostList(){
        return userPosts;
    }

    void addPost(Posts post){
        userPosts.push_back(post);
    }

    vector<Jobs> getUserJobAppliedList(){
        return userJobsApplied;
    }

    void addJobs(Jobs job){
        userJobsApplied.push_back(job);
    }
};




class Linkedin{
    private:
    vector<Users> usersDatabase;

    public:
    void addUsertoDatabase(Users u){
        usersDatabase.push_back(u);
    }

    vector<Users> getAllUsers(){
        return usersDatabase;
    }

    vector<Posts> getUserFeed(Users user){
        vector<Posts> userFeeds;
        vector<Users*> userConnections = user.getUserConnectionsList();

        for(Users* userConnection : userConnections){
            vector<Posts> friendPost = userConnection->getUserPostList();
            userFeeds.insert(userFeeds.end(), friendPost.begin(), friendPost.end());
        }

        return  userFeeds;
    }
};


int main(){
    Linkedin linkedin;

    Users user1("Harsh", "Software ENgineer", 1);
    Users user2("Alex", "Software ENgineer", 2);

    linkedin.addUsertoDatabase(user1);
    linkedin.addUsertoDatabase(user2);

    user1.addConnection(&user2);
    user2.addConnection(&user1);
    
    vector<Users*> harshConnections = user1.getUserConnectionsList();
    cout<<"Harsh Connection count is " <<harshConnections.size()<<"\n";
    cout<<"\n";
    
    Posts post1(1,"harsh is swe");
    Posts post2(2,"hello world");

    user2.addPost(post1);
    user2.addPost(post2);

    vector<Posts> alexPosts = user2.getUserPostList();
    cout<<"Alex Post count is " <<alexPosts.size()<<"\n";
    cout<<"\n";

    vector<Posts> harshFeedList = linkedin.getUserFeed(user1);
    cout<<"Harsh Feed is -----> \n";
    for(auto post : harshFeedList){
        cout<<post.getContent()<<"\n";
    }

}
