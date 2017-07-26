#include <fstream>
#include <string>



class CSVR
{
public:
    enum Skip
    {
        NONE,
        COLUMN,
        ROW
    };

    CSVR(const std::string& pcfFileName);
    virtual ~CSVR();

    bool nextCell(std::string* pnCellStr, const CSVR::Skip& pcfSkip = NONE);

private:
    std::ifstream iFile;
};
