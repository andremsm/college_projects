require "application_system_test_case"

class MajorsTest < ApplicationSystemTestCase
  setup do
    @major = majors(:one)
  end

  test "visiting the index" do
    visit majors_url
    assert_selector "h1", text: "Majors"
  end

  test "should create major" do
    visit majors_url
    click_on "New major"

    fill_in "Name", with: @major.name
    click_on "Create Major"

    assert_text "Major was successfully created"
    click_on "Back"
  end

  test "should update Major" do
    visit major_url(@major)
    click_on "Edit this major", match: :first

    fill_in "Name", with: @major.name
    click_on "Update Major"

    assert_text "Major was successfully updated"
    click_on "Back"
  end

  test "should destroy Major" do
    visit major_url(@major)
    click_on "Destroy this major", match: :first

    assert_text "Major was successfully destroyed"
  end
end
