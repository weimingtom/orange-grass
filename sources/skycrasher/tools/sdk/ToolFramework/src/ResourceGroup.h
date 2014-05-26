/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef RESOURCEGROUP_H_
#define RESOURCEGROUP_H_

#include <wx/wx.h>
#include <wx/treectrl.h>

enum ResourceType
{
	RESTYPE_TEXTURE,
	RESTYPE_MODEL,
	RESTYPE_TERRAIN,
	RESTYPE_MESH
};

struct ResourceGroup
{
    ResourceGroup () {}
	ResourceGroup (ResourceType _type, const wxString& _name)
	{
		name = _name;
		type = _type;
	}

	wxString		name;
	wxIcon			icon;
	wxTreeItemId	item;
	ResourceType	type;
};


struct ResourceItem : public wxTreeItemData
{
    ResourceItem () {}
	ResourceItem (ResourceType _type, const wxString& _name, const wxTreeItemId& _parentItem)
	{
		type = _type;
		name = _name;
        parentItem = _parentItem;
	}

	ResourceType	type;
	wxString		name;
    wxTreeItemId    parentItem;
};


enum EmitterParamType
{
	EMPRMTYPE_STRING,
	EMPRMTYPE_INT,
	EMPRMTYPE_FLOAT,
	EMPRMTYPE_COLOR
};


struct EmitterParamItem : public wxTreeItemData
{
	EmitterParamItem (EmitterParamType _type, void* _data)
	{
		type = _type;
		data = _data;
	}

	EmitterParamType	type;
	void*				data;
};

#endif