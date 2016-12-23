// Copyright 2016 Gamemakin LLC. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "LinterBatchRenamer"

/**
* FDlgBatchRenameTool
*
* Wrapper class for SDlgBatchRenameTool. This class creates and launches a dialog then awaits the
* result to return to the user.
*/
class FDlgBatchRenameTool
{
public:
	enum EResult
	{
		Cancel = 0,			// No/Cancel, normal usage would stop the current action
		Confirm = 1,		// Yes/Ok/Etc, normal usage would continue with action
	};

	FDlgBatchRenameTool();

	/**  Shows the dialog box and waits for the user to respond. */
	EResult ShowModal();

	FString Prefix;
	FString Suffix;
	bool bRemovePrefix;
	bool bRemoveSuffix;

	FString Find;
	FString Replace;

private:

	/** Cached pointer to the modal window */
	TSharedPtr<SWindow> DialogWindow;

	/** Cached pointer to the batch rename tool widget */
	TSharedPtr<class SDlgBatchRenameTool> DialogWidget;
};

/**
* Slate panel for batch renaming
*/
class SDlgBatchRenameTool : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDlgBatchRenameTool)
		{}
		/** Window in which this widget resides */
		SLATE_ATTRIBUTE(TSharedPtr<SWindow>, ParentWindow)
	SLATE_END_ARGS()

	/**
	* Constructs this widget
	*
	* @param	InArgs	The declaration data for this widget
	*/
	BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
	void Construct(const FArguments& InArgs)
	{
		UserResponse = FDlgBatchRenameTool::Cancel;
		ParentWindow = InArgs._ParentWindow.Get();

		this->ChildSlot[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(8.0f, 4.0f, 8.0f, 4.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Right)
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SNew(SBox)
							.WidthOverride(48.0f)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("BatchRenameToolDlgPrefix", "Prefix"))
								.Justification(ETextJustify::Right)
							]
						]
					+ SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SAssignNew(PrefixTextBox, SEditableTextBox)
						]
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(0.0f, 0.0f, 0.0f, 0.0f)
						[
							SAssignNew(PrefixRemoveBox, SCheckBox)
						]
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("BatchRenameToolDlgRemove", "Remove"))
						]
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(8.0f, 4.0f, 8.0f, 4.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Right)
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SNew(SBox)
							.WidthOverride(48.0f)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("BatchRenameToolDlgSuffix", "Suffix"))
								.Justification(ETextJustify::Right)
							]
						]
					+ SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SAssignNew(SuffixTextBox, SEditableTextBox)
						]
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(0.0f, 0.0f, 0.0f, 0.0f)
						[
							SAssignNew(SuffixRemoveBox, SCheckBox)
						]
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("BatchRenameToolDlgRemove", "Remove"))
						]
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(8.0f, 4.0f, 8.0f, 4.0f)
				[
					SNew(SSeparator)
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(8.0f, 4.0f, 8.0f, 4.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SNew(SBox)
							.WidthOverride(48.0f)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("BatchRenameToolDlgFind", "Find"))
								.Justification(ETextJustify::Right)
							]
						]
					+ SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SAssignNew(FindTextBox, SEditableTextBox)
						]
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(8.0f, 4.0f, 8.0f, 4.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SNew(SBox)
							.WidthOverride(48.0f)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("BatchRenameToolDlgReplace", "Replace"))
								.Justification(ETextJustify::Right)
							]
						]
					+ SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SAssignNew(ReplaceTextBox, SEditableTextBox)
						]
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(8.0f, 4.0f, 8.0f, 4.0f)
				[
					SNew(SSeparator)
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Right)
				.Padding(8.0f, 4.0f, 8.0f, 4.0f)
				[
					SNew(SUniformGridPanel)
						.SlotPadding(FEditorStyle::GetMargin("StandardDialog.SlotPadding"))
						.MinDesiredSlotWidth(FEditorStyle::GetFloat("StandardDialog.MinDesiredSlotWidth"))
						.MinDesiredSlotHeight(FEditorStyle::GetFloat("StandardDialog.MinDesiredSlotHeight"))
					+ SUniformGridPanel::Slot(0, 0)
					[
						SNew(SButton)
							.HAlign(HAlign_Center)
							.ContentPadding(FEditorStyle::GetMargin("StandardDialog.ContentPadding"))
							.OnClicked(this, &SDlgBatchRenameTool::OnButtonClick, FDlgBatchRenameTool::Confirm)
							.Text(LOCTEXT("SkeletonMergeOk", "OK"))
					]
					+ SUniformGridPanel::Slot(1, 0)
					[
						SNew(SButton)
							.HAlign(HAlign_Center)
							.ContentPadding(FEditorStyle::GetMargin("StandardDialog.ContentPadding"))
							.OnClicked(this, &SDlgBatchRenameTool::OnButtonClick, FDlgBatchRenameTool::Cancel)
							.Text(LOCTEXT("SkeletonMergeCancel", "Cancel"))
					]
				]
		];
	}
	END_SLATE_FUNCTION_BUILD_OPTIMIZATION

	/**
	* Returns the EResult of the button which the user pressed. Closing of the dialog
	* in any other way than clicking "Ok" results in this returning a "Cancel" value
	*/
	FDlgBatchRenameTool::EResult GetUserResponse() const
	{
		return UserResponse;
	}

private:

	/**
	* Handles when a button is pressed, should be bound with appropriate EResult Key
	*
	* @param ButtonID - The return type of the button which has been pressed.
	*/
	FReply OnButtonClick(FDlgBatchRenameTool::EResult ButtonID)
	{
		ParentWindow->RequestDestroyWindow();
		UserResponse = ButtonID;

		return FReply::Handled();
	}

	/** Stores the users response to this dialog */
	FDlgBatchRenameTool::EResult UserResponse;

	/** Pointer to the window which holds this Widget, required for modal control */
	TSharedPtr<SWindow>	ParentWindow;

public:

	TSharedPtr<SEditableTextBox> PrefixTextBox;
	TSharedPtr<SEditableTextBox> SuffixTextBox;
	TSharedPtr<SEditableTextBox> FindTextBox;
	TSharedPtr<SEditableTextBox> ReplaceTextBox;
	TSharedPtr<SCheckBox> PrefixRemoveBox;
	TSharedPtr<SCheckBox> SuffixRemoveBox;
};

#undef LOCTEXT_NAMESPACE