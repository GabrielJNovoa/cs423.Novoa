#pragma once

template <typename T>
class RefMan
{
private:
	T* target = nullptr;
	unsigned int refCount = 0;

	RefMan(T* newTarget) {
		target = newTarget;
	};

	void decreaseRefCount() {
		refCount -= 1;
		if (refCount <= 0) {
			delete target;
			delete this;
		}
	}

	RefMan(const RefMan<T>& other) = delete;
	RefMan(RefMan<T>&& other) = delete;

	RefMan<T>& operator=(const RefMan<T>& other) = delete;
	RefMan<T>& operator=(const RefMan<T>&& other) = delete;

	~RefMan() {};
public:
	class Ref {
	private:
		RefMan<T>* parent = nullptr;
		Ref(RefMan<T>* newParent) {
			parent = newParent;
			newParent->refCount += 1;
		};
	public:
		Ref() {}

		Ref(const Ref& other) {
			parent = other.parent;
			if (parent != nullptr) {
				parent->refCount += 1;
			}
		};

		Ref& operator=(const Ref& other) {
			if (parent != nullptr) {
				parent->decreaseRefCount();
			}
			parent = other.parent;
			if (parent != nullptr) {
				parent->refCount += 1;
			}
			return *this;
		}

		bool exists() {
			if (parent != nullptr) {
				return parent->exists();
			}
			else {
				return false;
			}
		}

		T& operator*() {
			return *(parent->target);
		}

		bool operator==(const Ref& other) {
			return parent == other.parent;
		}

		~Ref() {
			if (parent != nullptr) {
				parent->decreaseRefCount();
			}
		}

		friend class RefMan;
	};

	static RefMan<T>* makeRefMan(T* newTarget) {
		return new RefMan<T>(newTarget);
	}

	Ref makeRef() {
		Ref out(this);
		return out;
	}

	void disconnect() {
		target = nullptr;
		if (refCount <= 0 && target == nullptr) {
			delete this;
		}
	}

	bool exists() {
		return target != nullptr;
	}

	unsigned int getRefCount() {
		return refCount;
	}

	void debugSelfDestructDoNotUse() {
		delete this;
	}
	void debugTargetDestructDoNotUse() {
		delete this;
	}
};

