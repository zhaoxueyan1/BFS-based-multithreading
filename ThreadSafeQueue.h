#pragma once
#include"pch.h"
#include "ThreadPool.h"

const int MAXN = 5105039+2;
template<class T>
class Queue {
public:
	Queue() {
		cnt = 0;
		head = last = 0;
	}
	void push(T a) {
		data[last] = a;
		last = (last + 1) % MAXN;
		cnt ++ ;
	}
	T front() {
		return data[head];
	}
	void pop() {
		head = (head +1) % MAXN;
		cnt--;
	}
	bool empty() {
		return cnt == 0;
	}
	int size() {
		return this->cnt;
	}
	int cnt;
private:
	int head;
	int last;
	T data[MAXN];
	
};

template<class T, class Container = Queue<T>>
class ThreadSafeQueue {
public:
	ThreadSafeQueue() = default;

	void Push(T element) {
		std::lock_guard<std::mutex> lock(mutex_);
		//queue_.push(std::forward<Element>(element));
		queue_.push(element);
		not_empty_cv_.notify_one();
	}

	T Front() {
		std::lock_guard<std::mutex> lock(mutex_);
		T res = queue_.front();
		not_empty_cv_.notify_one();
		return res;
	}

	void WaitAndPop(T& t) {
		std::unique_lock<std::mutex> lock(mutex_);
		not_empty_cv_.wait(lock, []() {
			return !queue_.empty();
		});

		t = std::move(queue_.front());
		queue_.pop();
	}

	T WaitAndPop() {
		std::unique_lock<std::mutex> lock(mutex_);
		not_empty_cv_.wait(lock, [this]() {
			return !queue_.empty();
		});

		T t_ptr = queue_.front();
		queue_.pop();
		return t_ptr;
	}

	bool TryPop(T& t) {
		std::lock_guard<std::mutex> lock(mutex_);
		if (queue_.empty()) {
			return false;
		}

		t = std::move(queue_.front());
		queue_.pop();
		return true;
	}

	std::shared_ptr<T> TryPop() {
		std::lock_guard<std::mutex> lock(mutex_);
		if (queue_.empty()) {
			return std::shared_ptr<T>();
		}

		//t = std::move(queue_.front());
		std::shared_ptr<T> t_ptr = std::make_shared<T>(queue_.front());
		queue_.pop();

		return t_ptr;
	}

	bool IsEmpty() {
		std::lock_guard<std::mutex> lock(mutex_);
		return queue_.empty();
	}

private:
	ThreadSafeQueue(const ThreadSafeQueue&) = delete;
	ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
	ThreadSafeQueue(ThreadSafeQueue&&) = delete;
	ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;

private:
	Container queue_;
	int cnt;
	std::condition_variable not_empty_cv_;
	mutable std::mutex mutex_;
};
