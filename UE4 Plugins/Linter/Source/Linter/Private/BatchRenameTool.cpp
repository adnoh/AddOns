// Copyright 2016 Gamemakin LLC. All Rights Reserved.

#include "LinterPrivatePCH.h"
#include "BatchRenameTool.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "LinterBatchRenamer"

FDlgBatchRenameTool::FDlgBatchRenameTool()
	: bRemovePrefix(false)
	, bRemoveSuffix(false)
{
	if (FSlateApplication::IsInitialized())
	{
		DialogWindow = SNew(SWindow)
			.Title(LOCTEXT("BatchRenameToolDlgTitle", "Batch Rename Tool"))
			.SupportsMinimize(false).SupportsMaximize(false)
			.SaneWindowPlacement(true)
			.AutoCenter(EAutoCenter::PreferredWorkArea)
			.ClientSize(FVector2D(350, 165));

		TSharedPtr<SBorder> DialogWrapper =
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
			.Padding(4.0f)
			[
				SAssignNew(DialogWidget, SDlgBatchRenameTool)
				.ParentWindow(DialogWindow)
			];

		DialogWindow->SetContent(DialogWrapper.ToSharedRef());
	}
}

FDlgBatchRenameTool::EResult FDlgBatchRenameTool::ShowModal()
{
	//Show Dialog
	GEditor->EditorAddModalWindow(DialogWindow.ToSharedRef());
	EResult UserResponse = (EResult)DialogWidget->GetUserResponse();

	if (UserResponse == EResult::Confirm)
	{
		Prefix = DialogWidget->PrefixTextBox->GetText().ToString();
		Suffix = DialogWidget->SuffixTextBox->GetText().ToString();
		bRemovePrefix = DialogWidget->PrefixRemoveBox->IsChecked();
		bRemoveSuffix = DialogWidget->SuffixRemoveBox->IsChecked();

		Find = DialogWidget->FindTextBox->GetText().ToString();
		Replace = DialogWidget->ReplaceTextBox->GetText().ToString();

		// If no information is given, treat as canceled
		if (Prefix.IsEmpty() && Suffix.IsEmpty() && Find.IsEmpty())
		{
			return EResult::Cancel;
		}
	}
	return UserResponse;
}

#undef LOCTEXT_NAMESPACE