
#ifndef CONFIG_H_
#define CONFIG_H_

#if defined(UNITTEST)
#define BUFFER_SIZE 		(uint8_t) 50
#else
#define BUFFER_SIZE 		(uint8_t) 254
#endif

#endif /* CONFIG_H_ */
