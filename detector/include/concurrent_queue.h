#ifndef CONCURRENT_QUEUE
#define CONCURRENT_QUEUE

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <queue>

template<typename Data>
class concurrent_queue
{
public:
	void push(Data const& data) {
		boost::mutex::scoped_lock lock(the_mutex);
		the_queue.push(data);
		lock.unlock();
		the_condition_variable.notify_one();
	}

	bool empty() const {
		boost::mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	bool try_pop(Data& popped_value) {
		boost::mutex::scoped_lock lock(the_mutex);
		if(the_queue.empty()) {
			return false;
		}

		popped_value=the_queue.front();
		the_queue.pop();
		return true;
	}

	void wait_and_pop(Data& popped_value) {
		boost::mutex::scoped_lock lock(the_mutex);
		while(the_queue.empty()) {
			the_condition_variable.wait(lock);
		}

		popped_value=the_queue.front();
		the_queue.pop();
	}

	Data& wait_and_front() {
		boost::mutex::scoped_lock lock(the_mutex);
		while(the_queue.empty()) {
			the_condition_variable.wait(lock);
		}

		return the_queue.front();
	}
private:
	std::queue<Data> the_queue;
	mutable boost::mutex the_mutex;
	boost::condition_variable the_condition_variable;

};
#endif //CONCURRENT_QUEUE