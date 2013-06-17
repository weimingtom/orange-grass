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