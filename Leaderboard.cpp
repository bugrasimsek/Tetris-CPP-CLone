#include <fstream>
#include <iostream>
#include "Leaderboard.h"

// TODO: MAİNTAİN HIGH SCORE AND AT MAX 10 ITEMS
void Leaderboard::insert_new_entry(LeaderboardEntry * new_entry) {
    //Insert entry into the leaderboard linked list
    // "head_leaderboard_entry" member variable will always point to the highest all-times score,
    // and all other scores will be reachable from it via the "next_leaderboard_entry" member variable pointer.
    // Scores are sorted in descending order by the score.
    // Leaderboard size does not exceed 10 entries at any given time

    //if leaderboard is empty
//    if (head_leaderboard_entry == nullptr) {
//        head_leaderboard_entry = new_entry;
//        return;
//    }
//
//    //if leaderboard is not empty
//    LeaderboardEntry* current = head_leaderboard_entry;
//    LeaderboardEntry* previous = nullptr;
//
//    //find the correct position to insert the new entry
//    while (current != nullptr && current->score > new_entry->score) {
//        previous = current;
//        current = current->next_leaderboard_entry;
//    }
//
//    //if the new entry is the highest score
//
//    if (previous == nullptr) {
//        new_entry->next_leaderboard_entry = head_leaderboard_entry;
//        head_leaderboard_entry = new_entry;
//    }
//
//    //if the new entry is not the highest score
//    else {
//        previous->next_leaderboard_entry = new_entry;
//        new_entry->next_leaderboard_entry = current;
//    }
//
//    //if the leaderboard size exceeds 10 entries
//
//    //find the last entry
//    LeaderboardEntry* last = head_leaderboard_entry;
//    while (last->next_leaderboard_entry != nullptr) {
//        last = last->next_leaderboard_entry;
//    }
//
//    //delete the last entry
//    if (last != nullptr) {
//        delete last;
//        last = nullptr;
//    }

    ////// PREVIOUS CODE //////


    //If the leaderboard is empty, insert the new entry as the head
    if (head_leaderboard_entry == nullptr) {
        head_leaderboard_entry = new_entry;
    }

        //If the leaderboard is not empty, insert the new entry to the correct position
    else {
        LeaderboardEntry* current = head_leaderboard_entry;
        LeaderboardEntry* previous = nullptr;
        while (current != nullptr) {
            //If the new entry's score is higher than the current entry's score, insert the new entry before the current entry
            if (new_entry->score > current->score) {
                //If the new entry is the highest score, insert it as the head
                if (current == head_leaderboard_entry) {
                    new_entry->next_leaderboard_entry = head_leaderboard_entry;
                    head_leaderboard_entry = new_entry;
                }
                    //If the new entry is not the highest score, insert it before the current entry
                else {
                    previous->next_leaderboard_entry = new_entry;
                    new_entry->next_leaderboard_entry = current;
                }
                break;
            }
                //If the new entry's score is not higher than the current entry's score, insert the new entry after the current entry
            else {
                //If the new entry is the lowest score, insert it at the end
                if (current->next_leaderboard_entry == nullptr) {
                    current->next_leaderboard_entry = new_entry;
                    break;
                }
                    //If the new entry is not the lowest score, continue to the next entry
                else {
                    previous = current;
                    current = current->next_leaderboard_entry;
                }
            }
        }
    }

    entry_count++;

    //determine the highest score
    if (new_entry->score > highest_score) {
        highest_score = new_entry->score;
    }

    //If the leaderboard size exceeds 10 entries, delete the last entries until the size is 10
    while (entry_count > MAX_LEADERBOARD_SIZE) {
        LeaderboardEntry* current = head_leaderboard_entry;
        LeaderboardEntry* previous = nullptr;
        while (current->next_leaderboard_entry != nullptr) {
            previous = current;
            current = current->next_leaderboard_entry;
        }
        if (previous != nullptr) {
            previous->next_leaderboard_entry = nullptr;
        }
        delete current;
        entry_count--;
    }


}

// TODO: check "format specified in the PA instructions"
void Leaderboard::write_to_file(const string& filename) {


    //Write the latest leaderboard status to the given file in the format specified in the PA instructions
    ofstream file(filename);

    LeaderboardEntry* current = head_leaderboard_entry;
    while (current != nullptr) {
        //format timestamp of the entry
        time_t last_played = current->last_played;
        tm* localtimeLastPlayed = localtime(&last_played);
        string timestamp = to_string(localtimeLastPlayed->tm_hour) + ":" + to_string(localtimeLastPlayed->tm_min) + ":" + to_string(localtimeLastPlayed->tm_sec) + "/"
                           + to_string(localtimeLastPlayed->tm_mday) + "." + to_string(1 + localtimeLastPlayed->tm_mon) + "."
                           + to_string(1900 + localtimeLastPlayed->tm_year);

        file << current->score << " " << timestamp << " " << current->player_name << endl;
        current = current->next_leaderboard_entry;
    }

    file.close();


}

void Leaderboard::read_from_file(const string& filename) {

    /*
     * Read the stored leaderboard status from the given filename.
     * Create a new LeaderboardEntry instance for each entry in the file
     * Insert entry into the leaderboard linked list
     * "head_leaderboard_entry" member variable will point to the highest all-times score,
     * and all other scores will be reachable from it via the "next_leaderboard_entry" member variable pointer.
     */

    //Read the stored leaderboard status from the given filename.
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            //Create a new LeaderboardEntry instance for each entry in the file
            string score_str = line.substr(0, line.find(" "));
            unsigned long score = stoul(score_str);
            string last_played_str = line.substr(line.find(" ") + 1, line.find(" ", line.find(" ") + 1) - line.find(" ") - 1);
            time_t last_played = stoul(last_played_str);
            string player_name = line.substr(line.find(" ", line.find(" ") + 1) + 1);
            LeaderboardEntry* new_entry = new LeaderboardEntry(score, last_played, player_name);
            //Insert entry into the leaderboard linked list
            insert_new_entry(new_entry);
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file";
    }

    //print_leaderboard();
}


void Leaderboard::print_leaderboard() {
    /*
     * Leaderboard
     * -----------
     * <#order>. <player_name> <score> <timestamp formatted as %H:%M:%S/%d.%m.%Y>
     */

    //format timestamp <#order>. <player_name> <score> <timestamp formatted as %H:%M:%S/%d.%m.%Y>



    time_t now = time(0);
    tm* ltm = localtime(&now);
    string timestamp = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec) + "/"
                       + to_string(ltm->tm_mday) + "." + to_string(1 + ltm->tm_mon) + "."
                       + to_string(1900 + ltm->tm_year);

    //print leaderboard


    cout << "Leaderboard" << endl << "-----------" << endl;
    LeaderboardEntry* current = head_leaderboard_entry;
    int order = 1;
    while (current != nullptr) {
        //format timestamp of the entry
        time_t last_played = current->last_played;
        tm* ltm = localtime(&last_played);
        int day = ltm->tm_mday;
        string day_str = to_string(day);
        if(day < 10)
            day_str = "0" + to_string(day);


        string timestamp = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec) + "/"
                           + day_str + "." + to_string(1 + ltm->tm_mon) + "."
                           + to_string(1900 + ltm->tm_year);

        cout << order << ". " << current->player_name << " " << current->score << " " << timestamp << endl;
        order++;
        current = current->next_leaderboard_entry;
    }
}

// TODO: Free dynamically allocated memory used for storing leaderboard entries
Leaderboard::~Leaderboard() {
    //Free dynamically allocated memory used for storing leaderboard entries
    LeaderboardEntry* current = head_leaderboard_entry;
    LeaderboardEntry* next = nullptr;
    while (current != nullptr) {
        next = current->next_leaderboard_entry;
        delete current;
        current = next;
    }

    head_leaderboard_entry = nullptr;


}
