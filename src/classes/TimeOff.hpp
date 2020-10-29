#ifndef TIMEOFF_HPP
#define TIMEOFF_HPP

#include <vector>
#include <string>

class TimeOff
{
    private:
        std::string name;
        std::string label;
        std::vector<int> start_date;
        std::vector<int> end_date;
        int start_shift;
        int end_shift;
        std::string description;

    public:
        TimeOff(std::string n, std::vector<int> start_d, std::vector<int> end_d, int start_s, int end_s, std::string desc);
        TimeOff(std::string n);
        friend std::ostream &operator<<(std::ostream &output, const TimeOff &Toff);

        std::string get_name();
        void set_name(std::string str);
        std::string get_label();
        void set_label();

        int get_start_day() const;
        int get_start_month() const;
        int get_start_year() const;
        std::vector<int> get_start_date() const;

        int get_end_day() const;
        int get_end_month() const;
        int get_end_year() const;
        std::vector<int> get_end_date() const;

        int get_start_shift() const;
        int get_end_shift() const;

        std::string get_description() const;

        void set_start_day(int d);
        void set_start_month(int m);
        void set_start_year(int y);
        void set_start_date(int d, int m, int y);

        void set_end_day(int d);
        void set_end_month(int m);
        void set_end_year(int y);
        void set_end_date(int d, int m, int y);

        void set_start_shift(int s);
        void set_end_shift(int s);

        void set_description(std::string str);
};

#endif // TIMEOFF_HPP
