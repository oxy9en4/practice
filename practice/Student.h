#pragma once

struct Student {
    std::string name;
    int school_number;
    int korGrade;
    int engGrade;
    int mathGrade;
    int total;
    double avg;
    static int s_size;
};