#pragma once
public ref class MyBool {
public: MyBool(bool value) : value(value) { }
		MyBool% operator = (bool rhs) {
			value = rhs;
			return *this;
		}

		operator bool() {
			return value;
		}

private: bool value;
};