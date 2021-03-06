/* $Id: GVAttributeSchema.m,v 1.1 2008/02/11 12:34:07 glenlow Exp $ $Revision: 1.1 $ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2008 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#import "GVAttributeSchema.h"

static NSXMLDocument *_attributes = nil;
static NSTextFieldCell *_stringCell = nil;
static NSComboBoxCell *_enumCell = nil;

@implementation GVAttributeSchema

+ (void)initialize
{
	_attributes = [[NSXMLDocument alloc] initWithContentsOfURL:[NSURL fileURLWithPath:[[NSBundle mainBundle] pathForResource:@"attributes" ofType:@"xml"]] options:0 error:nil];
	
	NSFont* smallFont = [NSFont labelFontOfSize:[NSFont systemFontSizeForControlSize:NSSmallControlSize]];
	
	_stringCell = [[NSTextFieldCell alloc] init];
	[_stringCell setControlSize:NSSmallControlSize];
	[_stringCell setDrawsBackground:NO];
	[_stringCell setEditable:YES];
	[_stringCell setEnabled:YES];
	[_stringCell setFont:smallFont];

	_enumCell = [[NSComboBoxCell alloc] init];
	[_enumCell setBezeled:NO];
	[_enumCell setButtonBordered:NO];
	[_enumCell setCompletes:YES];
	[_enumCell setControlSize:NSSmallControlSize];
	[_enumCell setDrawsBackground:NO];
	[_enumCell setEditable:YES];
	[_enumCell setEnabled:YES];
	[_enumCell setFont:smallFont];
	[_enumCell setHasVerticalScroller:NO];
}

+ (NSArray*)attributeSchemasWithComponent:(NSString *)component
{
	NSMutableArray* attributeSchemas = [NSMutableArray array];
	for (NSXMLElement* element in [_attributes nodesForXPath:[NSString stringWithFormat:@"/xsd:schema/xsd:complexType[@name='%@']/xsd:attribute", component] error:nil])
		[attributeSchemas addObject:[[[GVAttributeSchema alloc] initWithXMLElement:element] autorelease]];
	return attributeSchemas;
}

- (id)initWithXMLElement:(NSXMLElement *)element
{
	if (self = [super init])
		_element = [element retain];
	return self;
}

- (NSString*)name
{
	return [[_element attributeForName:@"ref"] stringValue];
}

- (NSCell*)cell
{
	NSCell *typeCell = _stringCell;

	/* determine which cell to return */
	NSString *type = [[[_attributes nodesForXPath:[NSString stringWithFormat:@"/xsd:schema/xsd:attribute[@name='%@']/@type[1]", [self name]] error:nil] lastObject] stringValue];
	if (type) {
		if (![type hasPrefix:@"xsd:"]) {
				NSXMLElement *simpleType = [[_attributes nodesForXPath:[NSString stringWithFormat:@"/xsd:schema/xsd:simpleType[@name='%@'][1]", type] error:nil] lastObject];
				NSArray *enumerations = [simpleType nodesForXPath:@"xsd:restriction/xsd:enumeration" error:nil];
				if ([enumerations count]) {
					[_enumCell removeAllItems];
					for (NSXMLElement *enumeration in enumerations)
						[_enumCell addItemWithObjectValue: [[enumeration attributeForName: @"value"] stringValue]];
					typeCell = _enumCell;
				}
			}
	}
	
	/* determine the default value */
	NSString* defaultValue = [[_element attributeForName:@"default"] stringValue];
	if ([typeCell respondsToSelector:@selector(setPlaceholderString:)])
		[typeCell performSelector:@selector(setPlaceholderString:) withObject:defaultValue];
	return typeCell;
}

- (NSString*)documentation
{
	return [[[_attributes nodesForXPath:[NSString stringWithFormat:@"/xsd:schema/xsd:attribute[@name='%@']/xsd:annotation/xsd:documentation[1]", [self name]] error:nil] lastObject] XMLString];
}
	
- (void)dealloc
{
	[_element release];
	[super dealloc];
}


@end
