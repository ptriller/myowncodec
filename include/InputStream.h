/*
 * InputStream.h
 *
 *  Created on: 16.05.2016
 *      Author: ptriller
 */

#ifndef INPUTSTREAM_H_
#define INPUTSTREAM_H_


class InputStream {
public:
	virtual ~InputStream() {}

	virtual void close() = 0;

	virtual InputFrame *nextFrame() = 0;

};


#endif /* INPUTSTREAM_H_ */
