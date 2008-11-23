//
//  SimpleHTTPServer.h
//  Web2PDF Server
//
//  Created by Jürgen on 19.09.06.
//  Copyright 2006 Cultured Code.
//  License: Creative Commons Attribution 2.5 License
//           http://creativecommons.org/licenses/by/2.5/
//

#import <Cocoa/Cocoa.h>

@class TCHTTPConnection;

@interface TCHTTPServer : NSObject {
    unsigned port;
    id delegate;

    NSSocketPort *socketPort;
    NSFileHandle *fileHandle;
    NSMutableArray *connections;
    NSMutableArray *requests;    
    NSDictionary *currentRequest;
	
	NSOperationQueue *handlerQueue;
	NSMutableDictionary *handlers;
}

- (id)initWithTCPPort:(unsigned)po delegate:(id)dl;

- (NSArray *)connections;
- (NSArray *)requests;

- (void)closeConnection:(TCHTTPConnection *)connection;
- (void)newRequestWithURL:(NSURL *)url connection:(TCHTTPConnection *)connection;

// Request currently being processed
// Note: this need not be the most recently received request
- (NSDictionary *)currentRequest;

- (void)replyWithStatusCode:(int)code
                    headers:(NSDictionary *)headers
                       body:(NSData *)body;
- (void)replyWithData:(NSData *)data MIMEType:(NSString *)type;
- (void)replyWithStatusCode:(int)code message:(NSString *)message;

-(void)addHandlerForRegex:(NSString *)regexPath
				   target:(id)target
				selector:(SEL)selector;
@end
