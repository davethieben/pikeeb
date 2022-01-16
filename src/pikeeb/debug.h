#pragma once

#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef DEBUG
#define dprintf printf
#else
int dprintf(const char* format, ...);
#endif

#endif // _DEBUG_H
