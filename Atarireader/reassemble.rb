#!/usr/bin/env ruby

if ARGV.length != 2
    print("reassembly.rb {input dump txt file} {output binary}\n")
    exit 1
end

infile = File.open(ARGV[0], 'r')
outfile = File.open(ARGV[1], 'wb')
address = -1

infile.each_line { |line|
    line.strip!
    if (-1 == address)
        next if ('START' != line)
        address = 0
        next
    end
    break if ('END' == line)
    fields = line.split("\t")
    throw "Malformed line: #{line}" if 2 != fields.length
    throw "Malformed address" if fields[0][0] != '0' || fields[0][1] != 'x'
    throw "Malformed data" if fields[1].length != 32
    line_address = Integer(fields[0])
    line_data = fields[1]
    throw "Bad address jump" if address != line_address
    (0..15).each {
        byte_string = line_data[0, 2]
        line_data = line_data[2, line_data.length - 2]
        byte_value = byte_string.hex
        outfile.putc(byte_value)
    }
    address += 16;
}

infile.close()
outfile.close()
