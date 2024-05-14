//Improvement --> User Feed need to be created and we can have seperate class for feed and we can have filter according to time of post.

#include<bits/stdc++.h>
using namespace std;



class Posts{
    private:
    int postId;
    string content;
    int likes;
    int time;

    public:
        Posts(int postId, string content, int likes) : postId(postId), content(content), likes(likes), time(0) {}


    void setContent(string content){
        content = content;
    }

    int getPostId(){
        return postId;
    }

    string getContent(){
        return content;
    }

    int getLikes(){
        return likes;
    }

    int getPostTime(){
        return time;
    }

    void setLikes(int newLikesCount){
        likes = newLikesCount;
    }
};

class Users{
    private:
    int id;
    string name;
    vector<Users*> friendList;
    vector<Posts> userPosts;

    public:
    Users(int id, string name) : id(id), name(name) {}
    
    void addFriend(Users* user){
        friendList.push_back(user);
    }

    void addPost(Posts post){
        userPosts.push_back(post);
    }


    int getId(){
        return id;
    }

    string getName(){
        return name;
    }


    vector<Posts> getUserPosts(){
        return userPosts;
    }

    // need to store pointer here as we need to point as object sliciing ki issue slove karne kai liye
    vector<Users*> getUserFriendList(){
        return friendList;
    }
};



class SocialMedia{
    private:
    vector<Users> usersDatabase;
    public:
    void addUserToCollection(Users user){
        usersDatabase.push_back(user);
    }

    vector<Users> getAlluserFromDatabase(){
        return usersDatabase;
    } 

    vector<Posts> getUserFeed(Users user){
        vector<Posts> userFeed;
        vector<Users*> usersFriend = user.getUserFriendList();
        for (Users* friendUser : usersFriend) {
            vector<Posts> friendPost = friendUser->getUserPosts();
            userFeed.insert(userFeed.end(), friendPost.begin(), friendPost.end());
        }

        return userFeed;
    }

};

int main(){
    SocialMedia Facebook;
    
    Users user1(1, "Harsh");
    Users user2(2, "Shruti");

    Facebook.addUserToCollection(user1);
    Facebook.addUserToCollection(user2);

    // FriendShip friendConnection(user1, user2);
    vector<Users> facebookUsers =  Facebook.getAlluserFromDatabase();
    cout<<"Number of Users in Facebook "<<facebookUsers.size()<< "\n";
    for(auto x : facebookUsers){
        cout<<x.getName()<<"\n";
    }
    cout<<"\n";
    user1.addFriend(&user2);
    user2.addFriend(&user1);

   
    vector<Users*> user1Friend = user1.getUserFriendList();
    cout<<"Number of Friend of Harsh" << user1Friend.size()<<"\n";
    cout<<"Harsh Friend are \n";
    for(auto x : user1Friend){
        cout<<x->getName()<<"\n";
    }
    cout<<"\n";

    Posts p1(2, "harsh is good", 0);
    Posts p2(1, "hello World", 0);
    user2.addPost(p1);
    user2.addPost(p2);
    vector<Posts> user2Post =  user2.getUserPosts();

    cout<<"size is "<<user2Post.size()<<"\n";
    cout<<user2Post[0].getContent()<<"\n";

    vector<Posts> userPost = Facebook.getUserFeed(user1);
    cout<<"\n";
    cout<<"Harsh Feed is ----> \n";
    for(int i=0; i<userPost.size(); i++){
        cout<<userPost[i].getContent()<<"\n";
    }


}
