#include <fstream>
#include <string>



class CSVReader
{
public:
    enum Skip
    {
        NONE,
        COLUMN,
        ROW
    };

    CSVReader(const std::string& pcfFileName);
    virtual ~CSVReader();

    bool nextCell(std::string* pnCellStr);
    bool nextCell(const CSVReader::Skip& pcfSkip);

private:
    std::ifstream iFile;

    bool nextCell(std::string* pnCellStr, const CSVReader::Skip& pcfSkip);
};
