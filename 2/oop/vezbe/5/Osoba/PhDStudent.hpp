#ifndef PHDSTUDENT_HPP_INCLUDED
#define PHDSTUDENT_HPP_INCLUDED


class PhDStudent : public Student{
private:
    double prosecnaOcena;
public:
    PhDStudent() : Student(), prosecnaOcena(0){}
    PhDStudent(const char* ime, const char* p, int bi, double po) : Student(ime,p,bi), prosecnaOcena(po){}
    PhDStudent(const DinString& ime, const DinString& p, int bi, double po) : Student(ime,p,bi), prosecnaOcena(po){}
    PhDStudent(const Osoba& o, int bi, double po) : Student(o,bi), prosecnaOcena(po) {}
    PhDStudent(const Student& s, double po) : Student(s), prosecnaOcena(po) {}
    PhDStudent(const PhDStudent& phd) : Student((Student)phd), prosecnaOcena(0) {}

    void predstaviSe()const{
        Student::predstaviSe();
        cout<<"Moja prosecna ocena je "<<prosecnaOcena<<endl;
    }

};

#endif // PHDSTUDENT_HPP_INCLUDED
