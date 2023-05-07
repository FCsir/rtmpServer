
class Singleton
{

public:
    static Singleton& Get()
    {
        static Singleton s;

        return s;
    }


private:
    Singleton()
    {}

    Singleton(const Singleton& s) = delete;

};