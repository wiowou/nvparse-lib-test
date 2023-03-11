#include <string>
#include <vector>
#include <fstream>

#include "lest/lest.hpp"

#include "nvparse-lib/document.hpp"
#include "nvparse-lib/file.hpp"
#include "nvparse-lib/print.hpp"
#include "nvparse-lib/document_index.hpp"
#include "nvparse-lib/selector.hpp"

void path_to_string(std::string path, std::string &content) {
    std::ifstream fs(path.c_str());
    content.assign( (std::istreambuf_iterator<char>(fs) ),
                    (std::istreambuf_iterator<char>()   ) );
}

std::string pages_src("../pages-src/");
std::string pages_out("../pages-out/");
std::string pages_exp("../pages-exp/");

void compare_files(lest::env &lest_env, std::string filename) {
    std::cout << "checking: " << filename;
    SETUP(filename.c_str()) {
        nvparsehtml::File<char> html_file(pages_src + filename);
        EXPECT( html_file.data() != nullptr );
        nvparsehtml::DocumentNode<char> doc(html_file);
        nvparsehtml::DocumentIndex<char> indexer(&doc);
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
    std::cout << " PASSED" << std::endl;
}

const lest::test specification[] = {
    CASE("read, parse, print, comparison")
    {
        std::vector<std::string> filenames = { "index1.html" };
        for (auto filename : filenames)
            compare_files(lest_env, filename);
    },
    CASE("read and parse CSS selector expression")
    {
        std::string expression("[ id = 'baz' ]");
        nvparsehtml::Selector selector(expression);
    },
    CASE("read and parse CSS selector expression")
    {
        std::string expression(" #foo > .bar + div.k1.k2 [id='baz']:hello(2):not(:where(#yolo))::before");
        nvparsehtml::Selector selector(expression);
    },
};

int main( int argc, char * argv[] ) {
    return lest::run( specification, argc, argv );
}