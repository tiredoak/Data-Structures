/*
    Simulate the processing of network packets in a single
    processor machine.

    Input: first line contains size S of the buffer and number
           n of incoming packets. Each of the next n-lines
           contains 2 numbers, ith line contains the arrival
           time Ai and the processing time Pi of the ith packet.
           It is guaranteed the sequence is non-decreasing.
           1 <= S <= 10^5; 1 <= n <= 10^5; 0 <= Ai <= 10^6
           0 <= Pi <= 10^3 and Ai <= Ai+1
    Output: for each packet output either the moment in time
            when the processor began processing it or -1 if
            the packet was dropped.
*/

#include <iostream>
#include <deque>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {
        // When new request arrives, try to empty queue
        while (!finish_time_.empty() && finish_time_.front() <= request.arrival_time) {
            finish_time_.pop_front();
        }
        // If it's still full, we're forced to drop the packet
        if (size_ == finish_time_.size()) return Response(true, -1);
        // If the queue is empty it's either the very first packet or
        // the packet will be processed its arrival time
        if (finish_time_.empty()) {
            finish_time_.push_back(request.arrival_time + request.process_time);
            return Response(false, request.arrival_time);
        }
        // Add to queue
        Response reply = Response(false, finish_time_.back());
        finish_time_.push_back(finish_time_.back() + request.process_time);
        return reply;
    }
private:
    int size_;
    // Store the times when computer will finish processing
    // the packets
    std::deque <int> finish_time_;
};

// Returns vector with all input requests
std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

// Loops through requests and sends them to the buffer
std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)

        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

// Prints -1 if response was dropped and start time if processed
void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
