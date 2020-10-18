/**
 * Convert contents of given html source file into markdown,
 * save to given destination file
 *
 * @param arv[0] node
 * @param arv[1] tundown.js
 * @param arv[2] source file (html)
 * @param arv[3] destination file (markdown)
 */

// Make sure we got a filename on the command line.
if (process.argv.length < 4) {
    console.log('Usage: node ' + process.argv[1]
        + ' html_in_filename' + ' markdown_out_filename');
    process.exit(1);
}

// Read source file
var fs = require('fs')
    , filename = process.argv[2];

fs.readFile(filename, 'utf8', function(err, data) {
    if (err) {
        throw err;
    }

    var TurndownService = require('turndown');

    var turndownService = new TurndownService();
    var markdown = turndownService.turndown(data);

    console.log(markdown);
});
