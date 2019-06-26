#include <cstring>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include "miniz.h"
#include "util.h"

bool decompress(const char* source,std::vector<unsigned char>& dest,std::size_t in,std::size_t expected)
{
	if(!source)
	{
		qDebug() << "input string is empty,decompression failed.";
		return false;
	}

	int current = static_cast<int>(expected);
	std::vector<unsigned char> byteArray(expected/sizeof(unsigned char));
	z_stream stream;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	stream.next_in = (Bytef*)source;
	stream.avail_in = static_cast<unsigned int>(in);
	stream.next_out = (Bytef*)byteArray.data();
	stream.avail_out = static_cast<unsigned int>(expected);

	//we'd prefer to use inflateInit2 but it appears 
	//to be incorrect in miniz. This is fine for zlib
	//compressed data, but gzip compressed streams
	//will fail to inflate. IMO still preferable to
	//trying to build/link zlib
	if(inflateInit(&stream/*, 15 + 32*/) != Z_OK)
	{
		qDebug() << "inflate init failed.";
		return false;
	}

	int result = 0;
	do
	{
		result = inflate(&stream, Z_SYNC_FLUSH);

		switch (result)
		{
		case Z_NEED_DICT:
		case Z_STREAM_ERROR:
			result = Z_DATA_ERROR;
		case Z_DATA_ERROR:
			qDebug() << "If using gzip compression try using zlib instead";
		case Z_MEM_ERROR:
			inflateEnd(&stream);
			qDebug() << "z_mem_error error:"<<result;
			return false;
		}

		if (result != Z_STREAM_END)
		{
			int oldSize = current;
			current *= 2;
			std::vector<unsigned char> newArray(current / sizeof(unsigned char));
			std::memcpy(newArray.data(), byteArray.data(), current / 2);
			byteArray = std::move(newArray);

			stream.next_out = (Bytef*)(byteArray.data() + oldSize);
			stream.avail_out = oldSize;

		}
	} while (result != Z_STREAM_END);

	if (stream.avail_in != 0)
	{
		qDebug()<<"stream.avail_in is 0";
		qDebug()<<"zlib decompression failed.";
		return false;
	}

	const int outSize = current - stream.avail_out;
	inflateEnd(&stream);

	std::vector<unsigned char> newArray(outSize / sizeof(unsigned char));
	std::memcpy(newArray.data(), byteArray.data(), outSize);
	byteArray = std::move(newArray);

	//copy bytes to vector
	dest.insert(dest.begin(), byteArray.begin(), byteArray.end());
	return true;
}

std::string decodeBase64(const std::string& encode)
{
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	std::function<bool(unsigned char)> is_base64 =
		[](unsigned char c)->bool
	{
		return (isalnum(c) || (c == '+') || (c == '/'));
	};

	auto in_len = encode.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encode[in_] != '=') && is_base64(encode[in_]))
	{
		char_array_4[i++] = encode[in_]; in_++;
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
			{
				char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));
			}
			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
			{
				ret += char_array_3[i];
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; j++)
		{
			char_array_4[j] = 0;
		}

		for (j = 0; j < 4; j++)
		{
			char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));
		}

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
		{
			ret += char_array_3[j];
		}
	}

	return ret;
}

QString readAllBufferFromFile(const QString& filename)
{
	QFileInfo info(filename);
	if (!info.exists())
	{
		qDebug() << filename << " not exists";
		return QString();
	}

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "open file failed:" << filename;
		return QString();
	}

	QTextStream stream(&file);
	stream.setCodec("gb2312");
	QString buffer = stream.readAll();
	file.close();
	return buffer;
}

void saveToFile(const QString& filename, const QString& content)
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))
		return;

	QTextStream stream(&file);
	stream.setCodec("gb2312");
	stream << content;
	file.close();
}