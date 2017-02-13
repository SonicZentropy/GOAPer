#include "GOAPerEditor.h"
#include "GOAPStateCustomization.h"
#include "GOAPState.h"
#include "STextComboBox.h"
#include "SCheckBox.h"
#include "../Widgets/GOAPStateWidget.h"
#include "IPropertyUtilities.h"

#define LOCTEXT_NAMESPACE "GOAPStateCustomization"


TSharedRef<IPropertyTypeCustomization> FGOAPStateCustomization::MakeInstance()
{
	return MakeShareable(new FGOAPStateCustomization());
}

void FGOAPStateCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	PropertyUtilities = StructCustomizationUtils.GetPropertyUtilities();

	// Get the available options from our settings class
	for (auto& stateString : GOAPSettings->AState)
	{
		AvailableOptions.Add(MakeShareable<FString>(&stateString));
	}

	// Now fetch the handles to our child properties, and get their values
	uint32 NumChildren;
	StructPropertyHandle->GetNumChildren(NumChildren);

	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	{
		const TSharedPtr< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex);
		if (ChildHandle->GetProperty()->GetName() == TEXT("Key"))
		{
			KeyHandle = ChildHandle;
			ChildHandle->GetValue(Key);
		}
		if (ChildHandle->GetProperty()->GetName() == TEXT("Value"))
		{
			ValueHandle = ChildHandle;
			ChildHandle->GetValue(Value);
		}

	}

	


	HeaderRow
	.NameContent()
	[
		StructPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(500)
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		[
			SAssignNew(KeyComboBox, STextComboBox)
			.OptionsSource(&AvailableOptions)
			.OnSelectionChanged(this, &FGOAPStateCustomization::OnStateValueChanged)
			.InitiallySelectedItem(AvailableOptions[0])
		]
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Right)
		[
			SAssignNew(ValueCheckBox, SCheckBox)
			.IsChecked(Value)
		]
	];

}

void FGOAPStateCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	//Create further customization here
}


void FGOAPStateCustomization::OnStateValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	for (int32 i = 0; i < AvailableOptions.Num(); ++i)
	{
		if (AvailableOptions[i] == ItemSelected)
		{
			KeyHandle->SetValue(GOAPSettings->GetByteKey(ItemSelected));
		}
	}
	PropertyUtilities->RequestRefresh();
}

#undef LOCTEXT_NAMESPACE