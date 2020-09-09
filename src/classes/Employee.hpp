#ifndef __EMPLOYEE__
#define __EMPLOYEE__

#include <string>
#include <vector>

class Employee
{
	private:

		unsigned int id;

		std::string name;
		std::string role;

		bool closer;

		int max_h;
		int min_h;
		int max_d;
		int min_d;

		std::vector<std::vector<float>> avail;

        unsigned int priority;

	public:
		
        Employee(unsigned int, std::string, std::string, bool, int, int, int, int, unsigned int);
        Employee(const Employee &emp);
        Employee(Employee &&emp);
        ~Employee();

        Employee& operator=(Employee&& emp);

		friend std::ostream &operator<<(std::ostream &output, const Employee &Emp);

		unsigned int get_id() const;
        void set_id(unsigned int id);

		bool is_closer() const;
		void set_closer(bool b);

		std::string get_name() const;
		void set_name(std::string n);

		std::string get_role() const;
		void set_role(std::string r);

		int get_days_max() const;
		int get_days_min() const;
        int get_hours_max() const;
        int get_hours_min() const;

        void set_days_min(int i);
        void set_days_max(int i);
        void set_hours_min(int i);
        void set_hours_max(int i);

        unsigned int get_priority();
        void set_priority(unsigned int p);

		std::vector<float> get_avail(int day) const;
		void set_avail(int day, std::vector<float> vec);
        void set_avail(int day, int shift, float val);
};


#endif
