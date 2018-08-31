#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  auto findLadders(
      const string& begin_word, const string& end_word, const vector<string>& permitted_words) {
    add_word(begin_word);
    add_word(end_word);
    for (const string& word : permitted_words) {
      add_word(word);
      permitted_ids_.insert(id_by_word_[word]);
    }
    is_id_visited_.resize(id_by_word_.size());
    distantions_.resize(id_by_word_.size());

    vector<vector<string>> answer_ways;

    auto min_path_length = calculate_min_path_length();
    if (min_path_length == -1) {
      return answer_ways;
    }
    vector<size_t> way;
    calculate_all_ways(0, -1, 0, min_path_length, way);

    for (const auto& way : answer_id_ways_) {
      answer_ways.push_back({begin_word});
      for (auto id : way) {
        answer_ways.back().push_back(word_by_id_[id]);
      }
    }
    return answer_ways;
  }

private:
  size_t calculate_min_path_length() {
    queue<pair<size_t, size_t>> next_ids;
    next_ids.push({0, 0});
    is_id_visited_[0] = true;
    while (!next_ids.empty()) {
      auto id_now = next_ids.front().first;
      auto way_length_now = next_ids.front().second;
      distantions_[id_now] = way_length_now;
      if (id_now == 1) {
        return way_length_now;
      }
      next_ids.pop();
      auto neighbours = neighbours_by_id(id_now);
      for (auto next_id : neighbours) {
        if (!is_id_visited_[next_id]) {
          is_id_visited_[next_id] = true;
          next_ids.push({next_id, way_length_now + 1});
        }
      }
    }
    return -1;
  }

  void calculate_all_ways(
      size_t id_now,
      size_t id_previous,
      size_t length_now,
      size_t max_length,
      vector<size_t>& way_now
  ) {
    if (id_now == 1) {
      answer_id_ways_.push_back(way_now);
      return;
    }
    if (length_now == max_length) {
      return;
    }
    auto neighbours = neighbours_by_id(id_now);
    for (auto next_id : neighbours) {
      if (next_id != id_previous && distantions_[next_id] > distantions_[id_now]) {
        way_now.push_back(next_id);
        calculate_all_ways(next_id, id_now, length_now + 1, max_length, way_now);
        way_now.pop_back();
      }
    }
  }

  vector<size_t> neighbours_by_id(size_t id) {
    auto word_now = word_by_id_[id];
    auto next_word = word_now;
    vector<size_t> neighbours;
    for (size_t i = 0; i < next_word.size(); ++i) {
      for (char c = 'a'; c <= 'z'; ++c) {
        if (c != word_now[i]) {
          next_word[i] = c;
          if (id_by_word_.find(next_word) != id_by_word_.end()) {
            auto id = id_by_word_[next_word];
            if (permitted_ids_.find(id) != permitted_ids_.end()) {
              neighbours.push_back(id);
            }
          }
        }
      }
      next_word[i] = word_now[i];
    }
    return neighbours;
  }

  void add_word(const string& word) {
    if (id_by_word_.find(word) != id_by_word_.end()) {
      return;
    }
    auto id = id_by_word_.size();
    id_by_word_[word] = id;
    word_by_id_[id] = word;
  }

  vector<bool> is_id_visited_;
  vector<size_t> distantions_;
  vector<vector<size_t>> answer_id_ways_;
  unordered_map<string, size_t> id_by_word_;
  unordered_map<size_t, string> word_by_id_;
  unordered_set<size_t> permitted_ids_;
};

void test(
    const string& begin_word,
    const string& end_word,
    const vector<string>& permitted_words
) {
  clog << "[::test]: begin_word: " << begin_word << " end_word: " << end_word;
  clog << " permitted_words: ";
  for (const auto& word : permitted_words) {
    clog << word << ' ';
  }
  clog << endl;
  Solution solution;
  auto answer = solution.findLadders(begin_word, end_word, permitted_words);
  clog << "answer:\n";
  for (const auto& way : answer) {
    clog << "   ";
    for (const auto& word : way) {
      clog << word << ' ';
    }
    clog << endl;
  }
}

int main() {
  test("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"});
  test("hit", "cog", {"hot", "dot", "dog", "lot", "log"});
  test("cet",
      "ism",
      {"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"});
}
