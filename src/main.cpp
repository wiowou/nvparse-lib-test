#include <fstream>

#include "lest/lest.hpp"

#include "nvparse-lib/node.hpp"
#include "nvparse-lib/read.hpp"
#include "nvparse-lib/print.hpp"

void path_to_string(std::string path, std::string &content) {
    std::ifstream fs(path.c_str());
    content.assign( (std::istreambuf_iterator<char>(fs) ),
                    (std::istreambuf_iterator<char>()   ) );
}

const lest::test specification[] = {

CASE( "read, parse, print index1.html" )
{
    SETUP("index1.html") {
        std::string pages_src("../pages-src/");
        std::string pages_out("../pages-out/");
        std::string pages_exp("../pages-exp/");
        std::string filename("index1.html");

        nvparsehtml::File<char> html_file((pages_src + filename).c_str());
        EXPECT( html_file.data() != nullptr );
        nvparsehtml::DocumentNode<char> doc;
        doc.parse(html_file.data());
        EXPECT( doc.children_size() == 2 );

        std::fstream out((pages_out + filename).c_str(), std::ios::out);
        out << doc;
        out.close();

        std::string out_content;
        std::string expected_content;
        path_to_string(pages_out + filename, out_content);
        path_to_string(pages_exp + filename, expected_content);
        EXPECT(out_content == expected_content);
    }

},

};

int main( int argc, char * argv[] )
{
    return lest::run( specification, argc, argv );
}